/*
Magma - Abstraction layer over Khronos Vulkan API.
Copyright (C) 2018-2024 Victor Coda.

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

namespace magma
{
    class Image;
    class CommandBuffer;

    namespace helpers
    {
        /* Helper function to change layout of the image. As example,
           for VK_DESCRIPTOR_TYPE_STORAGE_IMAGE allowed layout is
           VK_IMAGE_LAYOUT_GENERAL, which isn't set by default. */

        void layoutTransition(std::shared_ptr<Image> image,
            VkImageLayout newLayout,
            std::shared_ptr<CommandBuffer> cmdBuffer);
        void batchLayoutTransition(const std::unordered_map<std::shared_ptr<Image>, VkImageLayout>& imageLayouts,
            std::shared_ptr<CommandBuffer> cmdBuffer);
    } // namespace helpers
} // namespace magma
