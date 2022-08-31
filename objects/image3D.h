/*
Magma - abstraction layer to facilitate usage of Khronos Vulkan API.
Copyright (C) 2018-2022 Victor Coda.

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
#include "image.h"

namespace magma
{
    /* Three-dimensional image. */

    class Image3D : public Image
    {
    public:
        explicit Image3D(std::shared_ptr<Device> device,
            VkFormat format,
            const VkExtent3D& extent,
            std::shared_ptr<Allocator> allocator = nullptr,
            const Descriptor& optional = Descriptor(),
            const Sharing& sharing = Sharing());
        explicit Image3D(std::shared_ptr<CommandBuffer> cmdBuffer,
            VkFormat format,
            const VkExtent3D& extent,
            std::shared_ptr<const SrcTransferBuffer> srcBuffer,
            const CopyLayout& bufferLayout = {0, 0, 0},
            std::shared_ptr<Allocator> allocator = nullptr,
            const Descriptor& optional = Descriptor(),
            const Sharing& sharing = Sharing());
    };
} // namespace magma
