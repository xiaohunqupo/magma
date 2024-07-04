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
#include "dispatchable.h"

namespace magma
{
    class Device;
    class CommandBuffer;
    class Semaphore;
#ifdef VK_KHR_timeline_semaphore
    class TimelineSemaphore;
#endif
#ifdef VK_KHR_external_semaphore_win32
    class D3d12ExternalSemaphore;
    #ifdef VK_KHR_timeline_semaphore
    class D3d12ExternalTimelineSemaphore;
    #endif
#endif // VK_KHR_external_semaphore_win32
    class Fence;
    class Swapchain;

    /* Queues provide an interface to the execution engines
       of a device. Commands for these execution engines are
       recorded into command buffers ahead of execution time.
       These command buffers are then submitted to queues
       with a queue submission command for execution in a
       number of batches. The device executes queue operations
       asynchronously with respect to the host. */

    class Queue : public Dispatchable<VkQueue>
    {
    public:
        VkQueueFlagBits getFlags() const noexcept { return flags; }
        uint32_t getFamilyIndex() const noexcept { return familyIndex; }
        uint32_t getIndex() const noexcept { return index; }
    #ifdef VK_EXT_swapchain_maintenance1
        void setPresentMode(VkPresentModeKHR presentMode_) noexcept { presentMode = presentMode_; }
        VkPresentModeKHR getPresentMode() const noexcept { return presentMode; }
    #endif // VK_EXT_swapchain_maintenance1
        void submit(std::shared_ptr<CommandBuffer> cmdBuffer,
            VkPipelineStageFlags waitDstStageMask = 0,
            std::shared_ptr<const Semaphore> waitSemaphore = nullptr,
            std::shared_ptr<Semaphore> signalSemaphore = nullptr,
            const std::unique_ptr<Fence>& fence = nullptr,
            const StructureChain& extendedInfo = StructureChain());
        void submit(const std::initializer_list<std::shared_ptr<CommandBuffer>> cmdBuffers,
            const std::initializer_list<VkPipelineStageFlags> waitDstStageMask = {},
            const std::initializer_list<std::shared_ptr<const Semaphore>> waitSemaphores = {},
            const std::initializer_list<std::shared_ptr<Semaphore>> signalSemaphores = {},
            const std::unique_ptr<Fence>& fence = nullptr,
            const StructureChain& extendedInfo = StructureChain());
    #ifdef VK_KHR_timeline_semaphore
        void submit(std::shared_ptr<const TimelineSemaphore> semaphore,
            uint64_t waitValue,
            uint64_t signalValue);
    #endif // VK_KHR_timeline_semaphore
    #ifdef VK_KHR_external_semaphore_win32
        void submit(std::shared_ptr<const D3d12ExternalSemaphore> semaphore,
            uint64_t waitValue,
            uint64_t signalValue);
        #ifdef VK_KHR_timeline_semaphore
        void submit(std::shared_ptr<const D3d12ExternalTimelineSemaphore> semaphore,
            uint64_t waitValue,
            uint64_t signalValue);
        #endif // VK_KHR_timeline_semaphore
    #endif // VK_KHR_external_semaphore_win32
    #ifdef VK_KHR_device_group
        void submitDeviceGroup(const std::initializer_list<std::shared_ptr<CommandBuffer>> cmdBuffers,
            const std::initializer_list<uint32_t> cmdBufferDeviceMasks = {},
            const std::initializer_list<VkPipelineStageFlags> waitDstStageMask = {},
            const std::initializer_list<std::shared_ptr<const Semaphore>> waitSemaphores = {},
            const std::initializer_list<uint32_t> waitSemaphoreDeviceIndices = {},
            const std::initializer_list<std::shared_ptr<Semaphore>> signalSemaphores = {},
            const std::initializer_list<uint32_t> signalSemaphoreDeviceIndices = {},
            const std::unique_ptr<Fence>& fence = nullptr);
    #endif // VK_KHR_device_group
        void waitIdle();
        void present(const std::unique_ptr<Swapchain>& swapchain,
            uint32_t imageIndex,
            std::shared_ptr<const Semaphore> waitSemaphore = nullptr,
            const std::unique_ptr<Fence>& presentFence = nullptr,
            const StructureChain& extendedInfo = StructureChain());
    #ifdef VK_KHR_display_swapchain
        void presentDisplay(const std::unique_ptr<Swapchain>& swapchain,
            uint32_t imageIndex,
            const VkRect2D& srcRect,
            const VkRect2D& dstRect,
            bool persistent,
            std::shared_ptr<const Semaphore> waitSemaphore = nullptr,
            const std::unique_ptr<Fence>& presentFence = nullptr);
    #endif // VK_KHR_display_swapchain
    #ifdef VK_NV_device_diagnostic_checkpoints
        std::vector<VkCheckpointDataNV> getCheckpoints(std::shared_ptr<const Device> device) const;
    #endif

    private:
        MAGMA_MAKE_SHARED(Queue)
        Queue(VkQueue handle, VkQueueFlagBits flags,
            uint32_t familyIndex, uint32_t index) noexcept;

        const VkQueueFlagBits flags;
        const uint32_t familyIndex;
        const uint32_t index;
    #ifdef VK_EXT_swapchain_maintenance1
        VkPresentModeKHR presentMode;
    #endif
        friend Device;
    };
} // namespace magma
