/*
Magma - Abstraction layer over Khronos Vulkan API.
Copyright (C) 2018-2023 Victor Coda.

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
#pragma once

// The granularity of the priorities is implementation-dependent. See:
// https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VkMemoryPriorityAllocateInfoEXT.html
#define MAGMA_MEMORY_PRIORITY_LOWEST 0.f
#define MAGMA_MEMORY_PRIORITY_LOW 0.25f
#define MAGMA_MEMORY_PRIORITY_DEFAULT 0.5f
#define MAGMA_MEMORY_PRIORITY_HIGH 0.75f
#define MAGMA_MEMORY_PRIORITY_HIGHEST 1.f

namespace magma
{
    class IDeviceMemory;

    /* Interface class of resource object. */

    class IResource : public IDestructible
    {
    public:
        enum class Class : uint32_t;
        virtual Class getResourceClass() const noexcept = 0;
        virtual const std::shared_ptr<IDeviceMemory>& getMemory() const noexcept = 0;
        virtual void bindMemory(std::shared_ptr<IDeviceMemory> memory,
            VkDeviceSize offset = 0) = 0;
    #ifdef VK_KHR_device_group
        virtual void bindMemoryDeviceGroup(std::shared_ptr<IDeviceMemory> memory,
            const std::vector<uint32_t>& deviceIndices,
            const std::vector<VkRect2D>& splitInstanceBindRegions = {},
            VkDeviceSize offset = 0) = 0;
    #endif // VK_KHR_device_group
        virtual void onDefragment() = 0;
    };

    /* Types of resources that occupy device memory. */

    enum class IResource::Class : uint32_t
    {
        Buffer, Image, AccelerationStructure
    };
} // namespace magma
