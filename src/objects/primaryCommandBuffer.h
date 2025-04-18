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
#include "commandBuffer.h"

namespace magma
{
    /* Primary command buffer, which can execute secondary
       command buffers, and which is submitted to the queue.
       As CommanPool allocates only objects of base CommandBuffer
       class, PrimaryCommandBuffer has its own constructor. */

    class PrimaryCommandBuffer : public CommandBuffer
    {
    public:
        explicit PrimaryCommandBuffer(lent_ptr<CommandPool> cmdPool);
        void executeCommands(lent_ptr<CommandBuffer> cmdBuffer) noexcept;
        void executeCommands(const std::initializer_list<lent_ptr<CommandBuffer>>& cmdBuffers) noexcept;
        void executeCommands(const std::vector<lent_ptr<CommandBuffer>>& cmdBuffers) noexcept;
    };
} // namespace magma
