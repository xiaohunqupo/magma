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

#if (VK_USE_64_BIT_PTR_DEFINES == 1)
namespace magma
{
    template<class Type>
    class NonDispatchable;
    template<class Type> using Pool = std::unordered_set<NonDispatchable<Type> *>;

    /* Resource pool stores pointers to different Vulkan objects
       that were created by device. Pool allows to keep statistics
       about resource usage, memory allocations etc. This may be used
       for application profiling, memory usage optimization and so on.
       Each logical device has it's own resource pool. */

    class ResourcePool final : NonCopyable
    {
    public:
        struct DeviceResources;
        struct PhysicalDeviceResources;

        std::mutex& getMutex() const noexcept { return mtx; }
        template<class Type> Pool<Type>& getPool();
        DeviceResources countDeviceResources() const;
        PhysicalDeviceResources countPhysicalDeviceResources() const;
        VkDeviceSize countAllocatedDeviceLocalMemory() const;
        VkDeviceSize countAllocatedHostVisibleMemory() const;
        VkDeviceSize countAllocatedBufferMemory() const;
        VkDeviceSize countAllocatedImageMemory() const;
        VkDeviceSize countAllocatedAccelerationStructureMemory() const;
        bool hasAnyDeviceResource() const;

    private:
        template<class NonDispatchableChild> using Fn = std::function<void(const NonDispatchableChild *)>;
        template<class NonDispatchableChild, class NonDispatchable>
        void foreach(const Pool<NonDispatchable>& pool, const Fn<NonDispatchableChild>& fn) const;

        Pool<VkSemaphore> semaphores;
        Pool<VkFence> fences;
        Pool<VkDeviceMemory> deviceMemories;
        Pool<VkBuffer> buffers;
        Pool<VkImage> images;
        Pool<VkEvent> events;
        Pool<VkQueryPool> queryPools;
        Pool<VkBufferView> bufferViews;
        Pool<VkImageView> imageViews;
        Pool<VkShaderModule> shaderModules;
        Pool<VkPipelineCache> pipelineCaches;
        Pool<VkPipelineLayout> pipelineLayouts;
        Pool<VkRenderPass> renderPasses;
        Pool<VkPipeline> pipelines;
        Pool<VkDescriptorSetLayout> descriptorSetLayouts;
        Pool<VkSampler> samplers;
        Pool<VkDescriptorPool> descriptorPools;
        Pool<VkDescriptorSet> descriptorSets;
        Pool<VkFramebuffer> framebuffers;
        Pool<VkCommandPool> commandPools;
    #ifdef VK_KHR_deferred_host_operations
        Pool<VkDeferredOperationKHR> deferredOperations;
    #endif
    #ifdef VK_KHR_sampler_ycbcr_conversion
        Pool<VkSamplerYcbcrConversionKHR> ycbcrSamplers;
    #endif
    #ifdef VK_KHR_surface
        Pool<VkSurfaceKHR> surfaces;
    #endif
    #ifdef VK_KHR_swapchain
        Pool<VkSwapchainKHR> swapchains;
    #endif
    #ifdef VK_KHR_display
        Pool<VkDisplayKHR> displays;
        Pool<VkDisplayModeKHR> displayModes;
    #endif
    #ifdef VK_EXT_debug_report
        Pool<VkDebugReportCallbackEXT> debugReportCallbacks;
    #endif
    #ifdef VK_EXT_debug_utils
        Pool<VkDebugUtilsMessengerEXT> debugUtilsMessengers;
    #endif
    #ifdef VK_EXT_private_data
        Pool<VkPrivateDataSlotEXT> privateDataSlots;
    #endif
    #ifdef VK_NV_ray_tracing
        Pool<VkAccelerationStructureNV> accelerationStructures;
    #endif
        mutable std::mutex mtx;
    };

    struct ResourcePool::DeviceResources
    {
        uint32_t semaphoreCount = 0;
        uint32_t fenceCount = 0;
        uint32_t deviceMemoryCount = 0;
        uint32_t bufferCount = 0;
        uint32_t image1DCount = 0;
        uint32_t image1DArrayCount = 0;
        uint32_t image2DCount = 0;
        uint32_t image2DArrayCount = 0;
        uint32_t image3DCount = 0;
        uint32_t eventCount = 0;
        uint32_t queryPoolCount = 0;
        uint32_t bufferViewCount = 0;
        uint32_t imageViewCount = 0;
        uint32_t shaderModuleCount = 0;
        uint32_t pipelineCacheCount = 0;
        uint32_t pipelineLayoutCount = 0;
        uint32_t renderPassCount = 0;
        uint32_t graphicsPipelineCount = 0;
        uint32_t computePipelineCount = 0;
        uint32_t rayTracingPipelineCount = 0;
        uint32_t descriptorSetLayoutCount = 0;
        uint32_t samplerCount = 0;
        uint32_t ycbcrSamplerCount = 0;
        uint32_t descriptorPoolCount = 0;
        uint32_t descriptorSetCount = 0;
        uint32_t framebufferCount = 0;
        uint32_t commandPoolCount = 0;
        uint32_t deferredOperationCount = 0;
        uint32_t swapchainCount = 0;
        uint32_t privateDataSlotCount = 0;
        uint32_t accelerationStructureCount = 0;
    };

    struct ResourcePool::PhysicalDeviceResources
    {
        uint32_t displayCount = 0;
        uint32_t displayModeCount = 0;
    };
} // namespace magma

#include "resourcePool.inl"
#endif // (VK_USE_64_BIT_PTR_DEFINES == 1)
