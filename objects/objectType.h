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
#include "../misc/compatibility.h"

namespace magma
{
#ifdef MAGMA_X64
    template<class Type>
    struct ObjectType
    {
        static constexpr VkObjectType getObjectType() { return VK_OBJECT_TYPE_UNKNOWN; }
    };

#define MAGMA_SPECIALIZE_OBJECT_TYPE(Type, objectType)\
    template<>\
    struct ObjectType<Type>\
    {\
        static constexpr VkObjectType getObjectType() { return objectType; }\
    };

    /* Template specializations for Vulkan object types. */

    MAGMA_SPECIALIZE_OBJECT_TYPE(VkInstance, VK_OBJECT_TYPE_INSTANCE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkPhysicalDevice, VK_OBJECT_TYPE_PHYSICAL_DEVICE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDevice, VK_OBJECT_TYPE_DEVICE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkQueue, VK_OBJECT_TYPE_QUEUE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkSemaphore, VK_OBJECT_TYPE_SEMAPHORE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkCommandBuffer, VK_OBJECT_TYPE_COMMAND_BUFFER)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkFence, VK_OBJECT_TYPE_FENCE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDeviceMemory, VK_OBJECT_TYPE_DEVICE_MEMORY)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkBuffer, VK_OBJECT_TYPE_BUFFER)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkImage, VK_OBJECT_TYPE_IMAGE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkEvent, VK_OBJECT_TYPE_EVENT)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkQueryPool, VK_OBJECT_TYPE_QUERY_POOL)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkBufferView, VK_OBJECT_TYPE_BUFFER_VIEW)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkImageView, VK_OBJECT_TYPE_IMAGE_VIEW)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkShaderModule, VK_OBJECT_TYPE_SHADER_MODULE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkPipelineCache, VK_OBJECT_TYPE_PIPELINE_CACHE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkPipelineLayout, VK_OBJECT_TYPE_PIPELINE_LAYOUT)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkRenderPass, VK_OBJECT_TYPE_RENDER_PASS)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkPipeline, VK_OBJECT_TYPE_PIPELINE)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDescriptorSetLayout, VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkSampler, VK_OBJECT_TYPE_SAMPLER)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDescriptorPool, VK_OBJECT_TYPE_DESCRIPTOR_POOL)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDescriptorSet, VK_OBJECT_TYPE_DESCRIPTOR_SET)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkFramebuffer, VK_OBJECT_TYPE_FRAMEBUFFER)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkCommandPool, VK_OBJECT_TYPE_COMMAND_POOL)
#ifdef VK_KHR_surface
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkSurfaceKHR, VK_OBJECT_TYPE_SURFACE_KHR)
#endif
#ifdef VK_KHR_swapchain
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkSwapchainKHR, VK_OBJECT_TYPE_SWAPCHAIN_KHR)
#endif
#ifdef VK_KHR_display
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDisplayKHR, VK_OBJECT_TYPE_DISPLAY_KHR)
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDisplayModeKHR, VK_OBJECT_TYPE_DISPLAY_MODE_KHR)
#endif
#ifdef VK_EXT_debug_report
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDebugReportCallbackEXT, VK_OBJECT_TYPE_DEBUG_REPORT_CALLBACK_EXT)
#endif
#ifdef VK_EXT_debug_utils
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkDebugUtilsMessengerEXT, VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT)
#endif
#ifdef VK_EXT_private_data
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkPrivateDataSlotEXT, VK_OBJECT_TYPE_PRIVATE_DATA_SLOT_EXT)
#endif
#ifdef VK_EXT_validation_cache
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkValidationCacheEXT, VK_OBJECT_TYPE_VALIDATION_CACHE_EXT)
#endif
#ifdef VK_NV_ray_tracing
    MAGMA_SPECIALIZE_OBJECT_TYPE(VkAccelerationStructureNV, VK_OBJECT_TYPE_ACCELERATION_STRUCTURE_NV)
#endif
#endif // MAGMA_X64
} // namespace magma
