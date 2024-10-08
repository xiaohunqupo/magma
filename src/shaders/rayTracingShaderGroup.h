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
#ifdef VK_KHR_ray_tracing_pipeline

namespace magma
{
    /* Ray tracing pipelines can contain multiple shader groups
       that can be bound individually. Each shader group behaves
       as if it was a pipeline using the shader group's state. */

    struct RayTracingShaderGroup : VkRayTracingShaderGroupCreateInfoKHR
    {
        constexpr hash_t hash() const noexcept;

    protected:
        constexpr RayTracingShaderGroup(VkRayTracingShaderGroupTypeKHR type,
            uint32_t generalShader,
            uint32_t closestHitShader,
            uint32_t anyHitShader,
            uint32_t intersectionShader,
            const void *captureReplayHandle) noexcept;
    };

    /* General shader group indicates a shader group with a single
       ray generation, miss, or callable shader in it. */

    struct GeneralRayTracingShaderGroup : RayTracingShaderGroup
    {
        constexpr GeneralRayTracingShaderGroup(uint32_t generalShader,
            const void *captureReplayHandle = nullptr) noexcept;
    };

    /* Triangles hit group specifies a shader group that only hits triangles
       and must not contain an intersection shader, only closest hit and
       any-hit shaders. */

    struct TrianglesHitRayTracingShaderGroup : RayTracingShaderGroup
    {
        constexpr TrianglesHitRayTracingShaderGroup(uint32_t closestHitShader,
            uint32_t anyHitShader = VK_SHADER_UNUSED_KHR,
            const void *captureReplayHandle = nullptr) noexcept;
    };

    /* Procedural hit group specifies a shader group that only intersects
       with custom geometry and must contain an intersection shader and may
       contain closest hit and any-hit shaders. */

    struct ProceduralHitRayTracingShaderGroup : RayTracingShaderGroup
    {
        constexpr ProceduralHitRayTracingShaderGroup(uint32_t intersectionShader,
            uint32_t closestHitShader = VK_SHADER_UNUSED_KHR,
            uint32_t anyHitShader = VK_SHADER_UNUSED_KHR,
            const void *captureReplayHandle = nullptr) noexcept;
    };
} // namespace magma

#include "rayTracingShaderGroup.inl"
#endif // VK_KHR_ray_tracing_pipeline
