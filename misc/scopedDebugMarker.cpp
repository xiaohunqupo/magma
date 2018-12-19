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
#include "scopedDebugMarker.h"
#include "../objects/commandBuffer.h"
#include "../utilities/hexColor.h"
#include "../internal/shared.h"

namespace magma
{
ScopedDebugMarker::ScopedDebugMarker(std::shared_ptr<CommandBuffer> cmdBuffer, const char *name) noexcept:
    ScopedDebugMarker(std::move(cmdBuffer), name, 0.f, 0.f, 0.f, 1.f)
{}

ScopedDebugMarker::ScopedDebugMarker(std::shared_ptr<CommandBuffer> cmdBuffer, const char *name,
    float r, float g, float b, float a /* 1 */) noexcept:
    cmdBuffer(std::move(cmdBuffer))
{
#ifdef MAGMA_DEBUG
    const float color[4] = {r, g, b, a};
    this->cmdBuffer->beginDebugLabel(name, color);
#elif defined(_MSC_VER)
    cmdBuffer;
    name;
    r; g; b; a;
#endif // MAGMA_DEBUG
}

ScopedDebugMarker::ScopedDebugMarker(std::shared_ptr<CommandBuffer> cmdBuffer, const char *name, const float color[4]) noexcept:
    cmdBuffer(std::move(cmdBuffer))
{
#ifdef MAGMA_DEBUG
    this->cmdBuffer->beginDebugLabel(name, color);
#elif defined(_MSC_VER)
    cmdBuffer;
    name;
    color;
#endif // MAGMA_DEBUG
}

ScopedDebugMarker::ScopedDebugMarker(std::shared_ptr<CommandBuffer> cmdBuffer, const char *name, uint32_t hexColor) noexcept:
    cmdBuffer(std::move(cmdBuffer))
{
#ifdef MAGMA_DEBUG
    float color[4];
    utilities::hexColorToFloat4(hexColor, color);
    this->cmdBuffer->beginDebugLabel(name, color);
#elif defined(_MSC_VER)
    cmdBuffer;
    name;
    hexColor;
#endif // MAGMA_DEBUG
}

ScopedDebugMarker::~ScopedDebugMarker()
{
#ifdef MAGMA_DEBUG
    this->cmdBuffer->endDebugLabel();
#endif
}
} // namespace magma
