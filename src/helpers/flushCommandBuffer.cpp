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
#include "pch.h"
#pragma hdrstop
#include "../objects/device.h"
#include "../objects/commandPool.h"
#include "../objects/commandBuffer.h"
#include "../objects/queue.h"
#include "../objects/fence.h"

namespace magma
{
namespace helpers
{
void flushCommandBuffer(std::shared_ptr<CommandBuffer> cmdBuffer)
{
    const std::shared_ptr<CommandPool>& cmdPool = cmdBuffer->getCommandPool();
    uint32_t queueFamilyIndex = cmdPool->getQueueFamilyIndex();
    std::shared_ptr<Queue> queue = cmdPool->getDevice()->getQueueByFamily(queueFamilyIndex);
    const std::shared_ptr<Fence>& fence = cmdBuffer->getFence();
    fence->reset();
    {
        queue->submit(cmdBuffer, 0, nullptr, nullptr, fence);
    }
    fence->wait();
    cmdBuffer->finishedExecution();
}
} // namespace helpers
} // namespace magma
