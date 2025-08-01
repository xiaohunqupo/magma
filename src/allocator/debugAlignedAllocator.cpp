/*
Magma - Abstraction layer over Khronos Vulkan API.
Copyright (C) 2018-2025 Victor Coda.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
#include "pch.h"
#pragma hdrstop
#include "debugAlignedAllocator.h"

namespace magma
{
DebugAlignedAllocator::DebugAlignedAllocator() noexcept:
    allocatedMemorySize(0ull),
    internalAllocatedMemorySize(0ull)
{
    numAllocations = {};
    numReallocations = {};
    numFrees = {};
    numInternalAllocations = {};
    numInternalFrees = {};
}

DebugAlignedAllocator::~DebugAlignedAllocator()
{
    MAGMA_ASSERT(!allocatedMemorySize);
    MAGMA_ASSERT(!internalAllocatedMemorySize);
    MAGMA_ASSERT(allocations.empty());
    for (uint32_t scope = VK_SYSTEM_ALLOCATION_SCOPE_COMMAND;
        scope <= VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE; ++scope)
    {   // TODO: write to log?
        MAGMA_ASSERT(numAllocations[scope] == numFrees[scope]);
    }
}

void *DebugAlignedAllocator::alloc(std::size_t size, std::size_t alignment,
    VkSystemAllocationScope allocationScope)
{
    MAGMA_ASSERT(core::powerOfTwo(alignment));
    void *ptr;
#if defined(_MSC_VER)
    ptr = _aligned_malloc(size, alignment);
#elif defined(__MINGW32__) || defined(__MINGW64__)
    ptr = __mingw_aligned_malloc(size, alignment);
#else
    MAGMA_ASSERT(alignment % sizeof(void *) == 0);
    const int result = posix_memalign(&ptr, alignment, size);
    if (result != 0) // posix_memalign() does not modify memptr on failure
        ptr = nullptr;
#endif // !_MSC_VER && !__MINGW__
    MAGMA_HANDLE_OUT_OF_MEMORY(ptr);
    // Add allocation
    std::lock_guard<std::shared_mutex> lock(mtx);
    allocations[ptr] = {size, allocationScope};
    allocatedMemorySize += size;
    ++numAllocations[allocationScope];
    return ptr;
}

void *DebugAlignedAllocator::realloc(void *original, std::size_t size, std::size_t alignment,
    VkSystemAllocationScope allocationScope)
{
    if (0 == size)
    {   // realloc(ptr, 0) equals to free()
        this->free(original);
        return nullptr;
    }
    if (!original)
        return alloc(size, alignment, allocationScope);
    const std::size_t oldSize = getAllocationSize(original);
    if (0 == oldSize)
        return nullptr;
    MAGMA_ASSERT(core::powerOfTwo(alignment));
    void *ptr;
#if defined(_MSC_VER)
    ptr = _aligned_realloc(original, size, alignment);
#else
    #if defined(__MINGW32__) || defined(__MINGW64__)
    ptr = __mingw_aligned_malloc(size, alignment);
    #else
    MAGMA_ASSERT(alignment % sizeof(void *) == 0);
    const int result = posix_memalign(&ptr, alignment, size);
    if (result != 0) // posix_memalign() does not modify memptr on failure
        ptr = nullptr;
    #endif // !__MINGW__
    if (ptr)
    {   // On Unix we need to copy memory between aligned blocks
        memcpy(ptr, original, std::min(size, oldSize));
    #if defined(__MINGW32__) || defined(__MINGW64__)
        __mingw_aligned_free(original);
    #else
        ::free(original);
    #endif
    }
#endif // !_MSC_VER
    MAGMA_HANDLE_OUT_OF_MEMORY(ptr);
    // Replace old allocation with a new one
    std::lock_guard<std::shared_mutex> lock(mtx);
    allocatedMemorySize -= oldSize;
    allocations.erase(original);
    allocations[ptr] = {size, allocationScope};
    allocatedMemorySize += size;
    ++numReallocations[allocationScope];
    return ptr;
}

void DebugAlignedAllocator::free(void *ptr) noexcept
{
    if (!ptr)
        return;
    std::lock_guard<std::shared_mutex> lock(mtx);
    auto it = allocations.find(ptr);
    MAGMA_ASSERT(it != allocations.end());
    if (it == allocations.end())
        return;
#if defined(_MSC_VER)
    _aligned_free(ptr);
#elif defined(__MINGW32__) || defined(__MINGW64__)
    __mingw_aligned_free(ptr);
#else
    ::free(ptr);
#endif
    // Delete allocation
    auto [size, allocationScope] = it->second;
    allocations.erase(it);
    allocatedMemorySize -= size;
    ++numFrees[allocationScope];
}

void DebugAlignedAllocator::internalAllocationNotification(std::size_t size,
    VkInternalAllocationType /* allocationType */,
    VkSystemAllocationScope allocationScope) noexcept
{
    std::lock_guard<std::shared_mutex> lock(mtx);
    internalAllocatedMemorySize += size;
    ++numInternalAllocations[allocationScope];
}

void DebugAlignedAllocator::internalFreeNotification(std::size_t size,
    VkInternalAllocationType /* allocationType */,
    VkSystemAllocationScope allocationScope) noexcept
{
    std::lock_guard<std::shared_mutex> lock(mtx);
    internalAllocatedMemorySize -= size;
    ++numInternalFrees[allocationScope];
}

AllocationStatistics DebugAlignedAllocator::getAllocationStatistics() const noexcept
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    AllocationStatistics statistics;
    statistics.allocatedMemorySize = allocatedMemorySize;
    statistics.internalAllocatedMemorySize = internalAllocatedMemorySize;
    statistics.allocations.aliveCommandAllocations = numAllocations[VK_SYSTEM_ALLOCATION_SCOPE_COMMAND] - numFrees[VK_SYSTEM_ALLOCATION_SCOPE_COMMAND];
    statistics.allocations.aliveObjectAllocations = numAllocations[VK_SYSTEM_ALLOCATION_SCOPE_OBJECT] - numFrees[VK_SYSTEM_ALLOCATION_SCOPE_OBJECT];
    statistics.allocations.aliveCacheAllocations = numAllocations[VK_SYSTEM_ALLOCATION_SCOPE_CACHE] - numFrees[VK_SYSTEM_ALLOCATION_SCOPE_CACHE];
    statistics.allocations.aliveDeviceAllocations = numAllocations[VK_SYSTEM_ALLOCATION_SCOPE_DEVICE] - numFrees[VK_SYSTEM_ALLOCATION_SCOPE_DEVICE];
    statistics.allocations.aliveInstanceAllocations = numAllocations[VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE] - numFrees[VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE];
    statistics.internalAllocations.aliveCommandAllocations = numInternalAllocations[VK_SYSTEM_ALLOCATION_SCOPE_COMMAND] - numInternalFrees[VK_SYSTEM_ALLOCATION_SCOPE_COMMAND];
    statistics.internalAllocations.aliveObjectAllocations = numInternalAllocations[VK_SYSTEM_ALLOCATION_SCOPE_OBJECT] - numInternalFrees[VK_SYSTEM_ALLOCATION_SCOPE_OBJECT];
    statistics.internalAllocations.aliveCacheAllocations = numInternalAllocations[VK_SYSTEM_ALLOCATION_SCOPE_CACHE] - numInternalFrees[VK_SYSTEM_ALLOCATION_SCOPE_CACHE];
    statistics.internalAllocations.aliveDeviceAllocations = numInternalAllocations[VK_SYSTEM_ALLOCATION_SCOPE_DEVICE] - numInternalFrees[VK_SYSTEM_ALLOCATION_SCOPE_DEVICE];
    statistics.internalAllocations.aliveInstanceAllocations = numInternalAllocations[VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE] - numInternalFrees[VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE];
    return statistics;
}

std::size_t DebugAlignedAllocator::getAllocationSize(void *ptr) const
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    auto it = allocations.find(ptr);
    MAGMA_ASSERT(it != allocations.end());
    if (it != allocations.end())
        return it->second.first;
#ifdef MAGMA_NO_EXCEPTIONS
    return 0;
#else
    throw std::out_of_range("alien memory pointer");
#endif
}
} // namespace magma
