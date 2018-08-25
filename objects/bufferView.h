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
#include "handle.h"

namespace magma
{
    class Buffer;

    /* A buffer view represents a contiguous range of a buffer and a specific format
       to be used to interpret the data. Buffer views are used to enable shaders
       to access buffer contents interpreted as formatted data. */

    class BufferView : public NonDispatchable<VkBufferView>
    {
    public:
        explicit BufferView(std::shared_ptr<const Buffer> resource,
            VkFormat format,
            VkDeviceSize offset = 0,
            VkDeviceSize range = VK_WHOLE_SIZE,
            std::shared_ptr<IAllocator> allocator = nullptr);
        ~BufferView();
        std::shared_ptr<const Buffer> getBuffer() const noexcept { return buffer; }

    private:
        std::shared_ptr<const Buffer> buffer;
    };
} // namespace magma
