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
#include "object.h"

namespace magma
{
    /* Dispatchable handle types are a pointer to an opaque type.
       This pointer may be used by layers as part of intercepting
       API commands, and thus each API command takes a dispatchable
       type as its first parameter. Each object of a dispatchable
       type must have a unique handle value during its lifetime. */

    template<class Type>
    class Dispatchable : public IObject,
        public Object<Type>
    {
        static_assert(sizeof(Type) == sizeof(intptr_t),
            "invalid size of dispatchable handle type");

    protected:
        Dispatchable(VkObjectType objectType,
            Type handle = VK_NULL_HANDLE) noexcept:
            Object<Type>(objectType, handle, nullptr) {}
        Dispatchable(VkObjectType objectType,
            std::shared_ptr<IAllocator> allocator,
            Type handle = VK_NULL_HANDLE) noexcept:
            Object<Type>(objectType, handle, std::move(allocator)) {}
        VkObjectType getObjectType() const noexcept override
            { return Object<Type>::getType(); }
        uint64_t getObjectHandle() const noexcept override
            { return reinterpret_cast<uint64_t>(Object<Type>::handle); }
        void setPrivateData(uint64_t) override {}
        uint64_t getPrivateData() const noexcept override { return 0ull; }
        bool nonDispatchable() const noexcept override { return false; }
    };
} // namespace magma
