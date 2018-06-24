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
#pragma once
#include <vector>
#include "handle.h"

namespace magma
{
    class Instance;
    class PhysicalDevice;

    class Display : public NonDispatchable<VkDisplayKHR>
    {
        Display(std::shared_ptr<const PhysicalDevice> physicalDevice,
            VkDisplayKHR handle, 
            uint32_t planeIndex) noexcept;
        friend PhysicalDevice;

    public:
        std::shared_ptr<const PhysicalDevice> getPhysicalDevice() const noexcept { return physicalDevice; }
        uint32_t getPlaneIndex() const noexcept { return planeIndex; }
        std::vector<VkDisplayModePropertiesKHR> getModeProperties() const;

    private:
        std::shared_ptr<const Instance> instance;
        std::shared_ptr<const PhysicalDevice> physicalDevice;
        uint32_t planeIndex;
    };
} // namespace magma
