/*
Magma - C++1x interface over Khronos Vulkan API.
Copyright (C) 2018 Victor Coda.

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
#include "deviceMemory.h"
#include "device.h"
#include "physicalDevice.h"
#include "../allocator/allocator.h"
#include "../misc/exception.h"
#include "../shared.h"

namespace magma
{
DeviceMemory::DeviceMemory(std::shared_ptr<const Device> device, VkDeviceSize size, VkMemoryPropertyFlags flags,
    std::shared_ptr<IAllocator> allocator /* nullptr */):
    NonDispatchable(VK_DEBUG_REPORT_OBJECT_TYPE_DEVICE_MEMORY_EXT, std::move(device), std::move(allocator)),
    size(size)
{
    VkMemoryAllocateInfo info;
    info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    info.pNext = nullptr;
    info.allocationSize = size;
    info.memoryTypeIndex = VK_MAX_MEMORY_TYPES;
    const VkPhysicalDeviceMemoryProperties& properties = this->device->getPhysicalDevice()->getMemoryProperties();
    for (uint32_t i = 0; i < properties.memoryTypeCount; ++i)
    {   // Try to find exact match
        if (properties.memoryTypes[i].propertyFlags == flags)
        {
            info.memoryTypeIndex = i;
            break;
        }
    }
    if (VK_MAX_MEMORY_TYPES == info.memoryTypeIndex)
    {   
        for (uint32_t i = 0; i < properties.memoryTypeCount; ++i)
        {   // Try to find any suitable memory type
            if ((properties.memoryTypes[i].propertyFlags & flags) == flags)
            {
                info.memoryTypeIndex = i;
                break;
            }
        }
        if (VK_MAX_MEMORY_TYPES == info.memoryTypeIndex)
            MAGMA_THROW("failed to find suitable memory type");
    }
    const VkResult allocate = vkAllocateMemory(MAGMA_HANDLE(device), &info, MAGMA_OPTIONAL_INSTANCE(allocator), &handle);
    MAGMA_THROW_FAILURE(allocate, "failed to allocate memory");
}

DeviceMemory::~DeviceMemory()
{
    vkFreeMemory(MAGMA_HANDLE(device), handle, MAGMA_OPTIONAL_INSTANCE(allocator));
}

void *DeviceMemory::map(
    VkDeviceSize offset /* 0 */, 
    VkDeviceSize size /* VK_WHOLE_SIZE */,
    VkMemoryMapFlags flags /* 0 */) noexcept
{
    void *data;
    const VkResult map = vkMapMemory(MAGMA_HANDLE(device), handle, offset, size, flags, &data);
    return (VK_SUCCESS == map) ? data : nullptr;
}

void DeviceMemory::unmap() noexcept
{
    vkUnmapMemory(*device, handle);
}

bool DeviceMemory::flushMappedRange(
    VkDeviceSize offset /* 0 */, 
    VkDeviceSize size /* VK_WHOLE_SIZE */) noexcept
{
    VkMappedMemoryRange memoryRange;
    memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memoryRange.pNext = nullptr;
    memoryRange.memory = handle;
    memoryRange.offset = offset;
    memoryRange.size = size;
    const VkResult flush = vkFlushMappedMemoryRanges(MAGMA_HANDLE(device), 1, &memoryRange);
    return (VK_SUCCESS == flush);
}

bool DeviceMemory::invalidateMappedRange(
    VkDeviceSize offset /* 0 */,
    VkDeviceSize size /* VK_WHOLE_SIZE */) noexcept
{
    VkMappedMemoryRange memoryRange;
    memoryRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
    memoryRange.pNext = nullptr;
    memoryRange.memory = handle;
    memoryRange.offset = offset;
    memoryRange.size = size;
    const VkResult invalidate = vkInvalidateMappedMemoryRanges(MAGMA_HANDLE(device), 1, &memoryRange);
    return (VK_SUCCESS == invalidate);
}
} // namespace magma
