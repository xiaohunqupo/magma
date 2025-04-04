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
    class Device;

    /* Allows to query whether feature has been enabled in one line.
       Feel free to add new features if necessary. */

    class FeatureQuery : NonCopyable
    {
    public:
        bool maintenanceEnabled(uint8_t versionIndex) const noexcept;
        bool negativeViewportHeightEnabled() const noexcept;
        bool separateDepthStencilLayoutsEnabled() const noexcept;
        bool extendedLinesEnabled() const noexcept;
        bool stippledLinesEnabled() const noexcept;

    private:
        MAGMA_MAKE_UNIQUE(FeatureQuery)
        FeatureQuery(const Device *device) noexcept;
        friend Device;

        const Device *device;
    };
} // namespace magma
