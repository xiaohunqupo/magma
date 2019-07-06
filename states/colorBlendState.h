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
#include <vector>
#include "../api/vulkan.h"
#include "../internal/nonCopyable.h"

namespace magma
{
    /* Per-target blending state for each individual color attachment. */

    struct ColorBlendAttachmentState : VkPipelineColorBlendAttachmentState
    {
        constexpr ColorBlendAttachmentState(bool blendEnable,
            VkBlendFactor srcBlendFactor,
            VkBlendFactor dstBlendFactor,
            VkBlendOp blendOp,
            VkColorComponentFlags colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT) noexcept;
        constexpr size_t hash() const noexcept;
        constexpr bool operator==(const ColorBlendAttachmentState&) const noexcept;
    };

    /* Blending combines the incoming source fragment's R, G, B, and A values
       with the destination R, G, B, and A values of each sample stored in the framebuffer
       at the fragment's location. Blending is performed for each pixel sample,
       rather than just once for each fragment. */

    struct ColorBlendState : VkPipelineColorBlendStateCreateInfo, internal::ConstexprNonCopyable
    {
        constexpr ColorBlendState(const ColorBlendAttachmentState& attachment,
            bool logicOpEnable = false,
            VkLogicOp logicOp = VK_LOGIC_OP_CLEAR,
            const std::initializer_list<float>& blendConstants = {1.f, 1.f, 1.f, 1.f});
        constexpr size_t hash() const noexcept;
        constexpr bool operator==(const ColorBlendState&) const noexcept;

    protected:
        ColorBlendState() {}
    };

    /* Managed color blend state takes care about array of blend attachment states and 
       thereof is copyable, but not constexpr-constructible. */

    struct ManagedColorBlendState final : ColorBlendState
    {
        ManagedColorBlendState(const std::vector<ColorBlendAttachmentState>& attachments,
            const std::initializer_list<float>& blendConstants = {1.f, 1.f, 1.f, 1.f});
        ManagedColorBlendState(const ColorBlendState&);
        ManagedColorBlendState(const ManagedColorBlendState&);
        ManagedColorBlendState& operator=(const ManagedColorBlendState&);
        ~ManagedColorBlendState();
        size_t hash() const noexcept;
        bool operator==(const ManagedColorBlendState&) const noexcept;
    };

    /* If logicOpEnable is VK_TRUE, then a logical operation selected by logicOp is applied
       between each color attachment and the fragment�s corresponding output value,
       and blending of all attachments is treated as if it were disabled. */

    struct ColorLogicOpState : ColorBlendState
    {
        constexpr ColorLogicOpState(const ColorBlendAttachmentState& attachment,
            VkLogicOp logicOp);
    };
} // namespace magma

#include "colorBlendState.inl"

namespace magma
{
    namespace blendstates
    {
        constexpr VkColorComponentFlags rWriteMask(VK_COLOR_COMPONENT_R_BIT);
        constexpr VkColorComponentFlags rgWriteMask(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT);
        constexpr VkColorComponentFlags rgbWriteMask(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT);
        constexpr VkColorComponentFlags rgbaWriteMask(VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);

        constexpr ColorBlendAttachmentState writeR(false, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rWriteMask);
        constexpr ColorBlendAttachmentState writeRg(false, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rgWriteMask);
        constexpr ColorBlendAttachmentState writeRgb(false, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rgbWriteMask);
        constexpr ColorBlendAttachmentState writeRgba(false, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rgbaWriteMask);

        constexpr ColorBlendAttachmentState addR(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rWriteMask);
        constexpr ColorBlendAttachmentState addRg(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rgWriteMask);
        constexpr ColorBlendAttachmentState addRgb(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rgbWriteMask);
        constexpr ColorBlendAttachmentState addRgba(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rgbaWriteMask);

        constexpr ColorBlendAttachmentState subtractR(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_SUBTRACT, rWriteMask);
        constexpr ColorBlendAttachmentState subtractRg(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_SUBTRACT, rgWriteMask);
        constexpr ColorBlendAttachmentState subtractRgb(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_SUBTRACT, rgbWriteMask);
        constexpr ColorBlendAttachmentState subtractRgba(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_SUBTRACT, rgbaWriteMask);

        constexpr ColorBlendAttachmentState reverseSubtractR(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_REVERSE_SUBTRACT, rWriteMask);
        constexpr ColorBlendAttachmentState reverseSubtractRg(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_REVERSE_SUBTRACT, rgWriteMask);
        constexpr ColorBlendAttachmentState reverseSubtractRgb(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_REVERSE_SUBTRACT, rgbWriteMask);
        constexpr ColorBlendAttachmentState reverseSubtractRgba(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_REVERSE_SUBTRACT, rgbaWriteMask);

        constexpr ColorBlendAttachmentState minR(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MIN, rWriteMask);
        constexpr ColorBlendAttachmentState minRg(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MIN, rgWriteMask);
        constexpr ColorBlendAttachmentState minRgb(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MIN, rgbWriteMask);
        constexpr ColorBlendAttachmentState minRgba(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MIN, rgbaWriteMask);

        constexpr ColorBlendAttachmentState maxR(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MAX, rWriteMask);
        constexpr ColorBlendAttachmentState maxRg(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MAX, rgWriteMask);
        constexpr ColorBlendAttachmentState maxRgb(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MAX, rgbWriteMask);
        constexpr ColorBlendAttachmentState maxRgba(true, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_MAX, rgbaWriteMask);

        constexpr ColorBlendAttachmentState normalR(true, VK_BLEND_FACTOR_SRC_ALPHA, VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, VK_BLEND_OP_ADD, rWriteMask);
        constexpr ColorBlendAttachmentState normalRg(true, VK_BLEND_FACTOR_SRC_ALPHA, VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, VK_BLEND_OP_ADD, rgWriteMask);
        constexpr ColorBlendAttachmentState normalRgb(true, VK_BLEND_FACTOR_SRC_ALPHA, VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, VK_BLEND_OP_ADD, rgbWriteMask);
        constexpr ColorBlendAttachmentState normalRgba(true, VK_BLEND_FACTOR_SRC_ALPHA, VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, VK_BLEND_OP_ADD, rgbaWriteMask);

        constexpr ColorBlendAttachmentState multiplyR(true, VK_BLEND_FACTOR_DST_COLOR, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rWriteMask);
        constexpr ColorBlendAttachmentState multiplyRg(true, VK_BLEND_FACTOR_DST_COLOR, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rgWriteMask);
        constexpr ColorBlendAttachmentState multiplyRgb(true, VK_BLEND_FACTOR_DST_COLOR, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rgbWriteMask);
        constexpr ColorBlendAttachmentState multiplyRgba(true, VK_BLEND_FACTOR_DST_COLOR, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, rgbaWriteMask);

        constexpr ColorBlendAttachmentState screenR(true, VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rWriteMask);
        constexpr ColorBlendAttachmentState screenRg(true, VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rgWriteMask);
        constexpr ColorBlendAttachmentState screenRgb(true, VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rgbWriteMask);
        constexpr ColorBlendAttachmentState screenRgba(true, VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR, VK_BLEND_FACTOR_ONE, VK_BLEND_OP_ADD, rgbaWriteMask);
    } // namespace blendstates

    namespace renderstates
    {
        constexpr ColorBlendState dontBlendWriteR(blendstates::writeR);
        constexpr ColorBlendState dontBlendWriteRg(blendstates::writeRg);
        constexpr ColorBlendState dontBlendWriteRgb(blendstates::writeRgb);
        constexpr ColorBlendState dontBlendWriteRgba(blendstates::writeRgba);

        constexpr ColorBlendState blendAddWriteR(blendstates::addR);
        constexpr ColorBlendState blendAddWriteRg(blendstates::addRg);
        constexpr ColorBlendState blendAddWriteRgb(blendstates::addRgb);
        constexpr ColorBlendState blendAddWriteRgba(blendstates::addRgba);

        constexpr ColorBlendState blendSubtractWriteR(blendstates::subtractR);
        constexpr ColorBlendState blendSubtractWriteRg(blendstates::subtractRg);
        constexpr ColorBlendState blendSubtractWriteRgb(blendstates::subtractRgb);
        constexpr ColorBlendState blendSubtractWriteRgba(blendstates::subtractRgba);

        constexpr ColorBlendState blendReverseSubtractWriteR(blendstates::reverseSubtractR);
        constexpr ColorBlendState blendReverseSubtractWriteRg(blendstates::reverseSubtractRg);
        constexpr ColorBlendState blendReverseSubtractWriteRgb(blendstates::reverseSubtractRgb);
        constexpr ColorBlendState blendReverseSubtractWriteRgba(blendstates::reverseSubtractRgba);

        constexpr ColorBlendState blendMinWriteR(blendstates::minR);
        constexpr ColorBlendState blendMinWriteRg(blendstates::minRg);
        constexpr ColorBlendState blendMinWriteRgb(blendstates::minRgb);
        constexpr ColorBlendState blendMinWriteRgba(blendstates::minRgba);

        constexpr ColorBlendState blendMaxWriteR(blendstates::maxRg);
        constexpr ColorBlendState blendMaxWriteRg(blendstates::maxRg);
        constexpr ColorBlendState blendMaxWriteRgb(blendstates::maxRgb);
        constexpr ColorBlendState blendMaxWriteRgba(blendstates::maxRgba);

        constexpr ColorBlendState blendNormalWriteR(blendstates::normalR);
        constexpr ColorBlendState blendNormalWriteRg(blendstates::normalRg);
        constexpr ColorBlendState blendNormalWriteRgb(blendstates::normalRgb);
        constexpr ColorBlendState blendNormalWriteRgba(blendstates::normalRgba);

        constexpr ColorBlendState blendMultiplyWriteR(blendstates::multiplyR);
        constexpr ColorBlendState blendMultiplyWriteRg(blendstates::multiplyRg);
        constexpr ColorBlendState blendMultiplyWriteRgb(blendstates::multiplyRgb);
        constexpr ColorBlendState blendMultiplyWriteRgba(blendstates::multiplyRgba);

        constexpr ColorBlendState blendScreenWriteR(blendstates::screenR);
        constexpr ColorBlendState blendScreenWriteRg(blendstates::screenRg);
        constexpr ColorBlendState blendScreenWriteRgb(blendstates::screenRgb);
        constexpr ColorBlendState blendScreenWriteRgba(blendstates::screenRgba);

        constexpr ColorLogicOpState logicClearWriteR(blendstates::writeR, VK_LOGIC_OP_CLEAR);
        constexpr ColorLogicOpState logicAndWriteR(blendstates::writeR, VK_LOGIC_OP_AND);
        constexpr ColorLogicOpState logicReverseAndWriteR(blendstates::writeR, VK_LOGIC_OP_AND_REVERSE);
        constexpr ColorLogicOpState logicCopyWriteR(blendstates::writeR, VK_LOGIC_OP_COPY);
        constexpr ColorLogicOpState logicInvertedAndWriteR(blendstates::writeR, VK_LOGIC_OP_AND_INVERTED);
        constexpr ColorLogicOpState logicNoOpWriteR(blendstates::writeR, VK_LOGIC_OP_NO_OP);
        constexpr ColorLogicOpState logicXorWriteR(blendstates::writeR, VK_LOGIC_OP_XOR);
        constexpr ColorLogicOpState logicOrWriteR(blendstates::writeR, VK_LOGIC_OP_OR);
        constexpr ColorLogicOpState logicNorWriteR(blendstates::writeR, VK_LOGIC_OP_NOR);
        constexpr ColorLogicOpState logicEquivalentWriteR(blendstates::writeR, VK_LOGIC_OP_EQUIVALENT);
        constexpr ColorLogicOpState logicInvertR(blendstates::writeR, VK_LOGIC_OP_INVERT);
        constexpr ColorLogicOpState logicReverseOrWriteR(blendstates::writeR, VK_LOGIC_OP_OR_REVERSE);
        constexpr ColorLogicOpState logicInvertedCopyWriteR(blendstates::writeR, VK_LOGIC_OP_COPY_INVERTED);
        constexpr ColorLogicOpState logicInvertedOrWriteR(blendstates::writeR, VK_LOGIC_OP_OR_INVERTED);
        constexpr ColorLogicOpState logicNandWriteR(blendstates::writeR, VK_LOGIC_OP_NAND);
        constexpr ColorLogicOpState logicSetWriteR(blendstates::writeR, VK_LOGIC_OP_SET);

        constexpr ColorLogicOpState logicClearWriteRg(blendstates::writeRg, VK_LOGIC_OP_CLEAR);
        constexpr ColorLogicOpState logicAndWriteRg(blendstates::writeRg, VK_LOGIC_OP_AND);
        constexpr ColorLogicOpState logicReverseAndWriteRg(blendstates::writeRg, VK_LOGIC_OP_AND_REVERSE);
        constexpr ColorLogicOpState logicCopyWriteRg(blendstates::writeRg, VK_LOGIC_OP_COPY);
        constexpr ColorLogicOpState logicInvertedAndWriteRg(blendstates::writeRg, VK_LOGIC_OP_AND_INVERTED);
        constexpr ColorLogicOpState logicNoOpWriteRg(blendstates::writeRg, VK_LOGIC_OP_NO_OP);
        constexpr ColorLogicOpState logicXorWriteRg(blendstates::writeRg, VK_LOGIC_OP_XOR);
        constexpr ColorLogicOpState logicOrWriteRg(blendstates::writeRg, VK_LOGIC_OP_OR);
        constexpr ColorLogicOpState logicNorWriteRg(blendstates::writeRg, VK_LOGIC_OP_NOR);
        constexpr ColorLogicOpState logicEquivalentWriteRg(blendstates::writeRg, VK_LOGIC_OP_EQUIVALENT);
        constexpr ColorLogicOpState logicInvertRg(blendstates::writeRg, VK_LOGIC_OP_INVERT);
        constexpr ColorLogicOpState logicReverseOrWriteRg(blendstates::writeRg, VK_LOGIC_OP_OR_REVERSE);
        constexpr ColorLogicOpState logicInvertedCopyWriteRg(blendstates::writeRg, VK_LOGIC_OP_COPY_INVERTED);
        constexpr ColorLogicOpState logicInvertedOrWriteRg(blendstates::writeRg, VK_LOGIC_OP_OR_INVERTED);
        constexpr ColorLogicOpState logicNandWriteRg(blendstates::writeRg, VK_LOGIC_OP_NAND);
        constexpr ColorLogicOpState logicSetWriteRg(blendstates::writeRg, VK_LOGIC_OP_SET);

        constexpr ColorLogicOpState logicClearWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_CLEAR);
        constexpr ColorLogicOpState logicAndWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_AND);
        constexpr ColorLogicOpState logicReverseAndWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_AND_REVERSE);
        constexpr ColorLogicOpState logicCopyWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_COPY);
        constexpr ColorLogicOpState logicInvertedAndWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_AND_INVERTED);
        constexpr ColorLogicOpState logicNoOpWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_NO_OP);
        constexpr ColorLogicOpState logicXorWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_XOR);
        constexpr ColorLogicOpState logicOrWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_OR);
        constexpr ColorLogicOpState logicNorWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_NOR);
        constexpr ColorLogicOpState logicEquivalentWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_EQUIVALENT);
        constexpr ColorLogicOpState logicInvertRgb(blendstates::writeRgb, VK_LOGIC_OP_INVERT);
        constexpr ColorLogicOpState logicReverseOrWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_OR_REVERSE);
        constexpr ColorLogicOpState logicInvertedCopyWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_COPY_INVERTED);
        constexpr ColorLogicOpState logicInvertedOrWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_OR_INVERTED);
        constexpr ColorLogicOpState logicNandWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_NAND);
        constexpr ColorLogicOpState logicSetWriteRgb(blendstates::writeRgb, VK_LOGIC_OP_SET);

        constexpr ColorLogicOpState logicClearWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_CLEAR);
        constexpr ColorLogicOpState logicAndWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_AND);
        constexpr ColorLogicOpState logicReverseAndWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_AND_REVERSE);
        constexpr ColorLogicOpState logicCopyWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_COPY);
        constexpr ColorLogicOpState logicInvertedAndWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_AND_INVERTED);
        constexpr ColorLogicOpState logicNoOpWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_NO_OP);
        constexpr ColorLogicOpState logicXorWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_XOR);
        constexpr ColorLogicOpState logicOrWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_OR);
        constexpr ColorLogicOpState logicNorWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_NOR);
        constexpr ColorLogicOpState logicEquivalentWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_EQUIVALENT);
        constexpr ColorLogicOpState logicInvertRgba(blendstates::writeRgba, VK_LOGIC_OP_INVERT);
        constexpr ColorLogicOpState logicReverseOrWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_OR_REVERSE);
        constexpr ColorLogicOpState logicInvertedCopyWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_COPY_INVERTED);
        constexpr ColorLogicOpState logicInvertedOrWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_OR_INVERTED);
        constexpr ColorLogicOpState logicNandWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_NAND);
        constexpr ColorLogicOpState logicSetWriteRgba(blendstates::writeRgba, VK_LOGIC_OP_SET);
    } // namespace renderstates
} // namespace magma
