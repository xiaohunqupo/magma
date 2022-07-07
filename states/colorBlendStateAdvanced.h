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
#include "colorBlendState.h"

namespace magma
{
    /* This extension adds a number of "advanced" blending operations that can be
       used to perform new color blending operations, many of which are more
       complex than the standard blend modes provided by unextended Vulkan. */

    struct AdvancedColorBlendAttachmentState : VkPipelineColorBlendAttachmentState
    {
    public:
        constexpr AdvancedColorBlendAttachmentState(VkBlendOp advancedBlendOp,
            VkColorComponentFlags colorWriteMask = colormask::rgba) noexcept;
        constexpr hash_t hash() const noexcept;
        constexpr bool operator==(const AdvancedColorBlendAttachmentState&) const noexcept;
    };

    /* For explanation, see
       https://www.khronos.org/registry/OpenGL/extensions/NV/NV_blend_equation_advanced.txt */

#ifdef VK_EXT_blend_operation_advanced
    struct AdvancedColorBlendState final : ColorBlendState
    {
    public:
        explicit AdvancedColorBlendState(const AdvancedColorBlendAttachmentState& attachment,
            bool srcPremultiplied,
            bool dstPremultiplied,
            VkBlendOverlapEXT blendOverlap);
        explicit AdvancedColorBlendState(const std::initializer_list<AdvancedColorBlendAttachmentState>& attachments,
            bool srcPremultiplied,
            bool dstPremultiplied,
            VkBlendOverlapEXT blendOverlap);
        explicit AdvancedColorBlendState(const std::vector<AdvancedColorBlendAttachmentState>& attachments,
            bool srcPremultiplied,
            bool dstPremultiplied,
            VkBlendOverlapEXT blendOverlap);
        AdvancedColorBlendState(const AdvancedColorBlendState&);
        AdvancedColorBlendState& operator=(const AdvancedColorBlendState&);
        ~AdvancedColorBlendState();
        hash_t hash() const noexcept;
        bool operator==(const AdvancedColorBlendState&) const noexcept;
    };
#endif // VK_EXT_blend_operation_advanced
} // namespace magma

#include "colorBlendStateAdvanced.inl"

namespace magma
{
    namespace blendstate
    {
#ifdef VK_EXT_blend_operation_advanced
        namespace advanced
        {
            constexpr AdvancedColorBlendAttachmentState blendZeroR(VK_BLEND_OP_ZERO_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendSrcR(VK_BLEND_OP_SRC_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDstR(VK_BLEND_OP_DST_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendSrcOverR(VK_BLEND_OP_SRC_OVER_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDstOverR(VK_BLEND_OP_DST_OVER_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendSrcInR(VK_BLEND_OP_SRC_IN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDstInR(VK_BLEND_OP_DST_IN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendSrcOutR(VK_BLEND_OP_SRC_OUT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDstOutR(VK_BLEND_OP_DST_OUT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendSrcAtopR(VK_BLEND_OP_SRC_ATOP_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDstAtopR(VK_BLEND_OP_DST_ATOP_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendXorR(VK_BLEND_OP_XOR_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendMultiplyR(VK_BLEND_OP_MULTIPLY_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendScreenR(VK_BLEND_OP_SCREEN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendOverlayR(VK_BLEND_OP_OVERLAY_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDarkenR(VK_BLEND_OP_DARKEN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendLightenR(VK_BLEND_OP_LIGHTEN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendColorDodgeR(VK_BLEND_OP_COLORDODGE_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendColorBurnR(VK_BLEND_OP_COLORBURN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendHardLightR(VK_BLEND_OP_HARDLIGHT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendSoftLightR(VK_BLEND_OP_SOFTLIGHT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendDifferenceR(VK_BLEND_OP_DIFFERENCE_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendExclusionR(VK_BLEND_OP_EXCLUSION_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendInvertR(VK_BLEND_OP_INVERT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendInvertRgbR(VK_BLEND_OP_INVERT_RGB_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendLinearDodgeR(VK_BLEND_OP_LINEARDODGE_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendLinearBurnR(VK_BLEND_OP_LINEARBURN_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendVividLightR(VK_BLEND_OP_VIVIDLIGHT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendLinearLightR(VK_BLEND_OP_LINEARLIGHT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendPinLightR(VK_BLEND_OP_PINLIGHT_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendHardMixR(VK_BLEND_OP_HARDMIX_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendHslHueR(VK_BLEND_OP_HSL_HUE_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendHslSaturationR(VK_BLEND_OP_HSL_SATURATION_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendHslColorR(VK_BLEND_OP_HSL_COLOR_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendHslLuminosityR(VK_BLEND_OP_HSL_LUMINOSITY_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendPlusR(VK_BLEND_OP_PLUS_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedR(VK_BLEND_OP_PLUS_CLAMPED_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedAlphaR(VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendPlusDarkenR(VK_BLEND_OP_PLUS_DARKER_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendMinusR(VK_BLEND_OP_MINUS_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendMinusClampedR(VK_BLEND_OP_MINUS_CLAMPED_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendContrastR(VK_BLEND_OP_CONTRAST_EXT, colormask::r);
            constexpr AdvancedColorBlendAttachmentState blendInvertOvgR(VK_BLEND_OP_INVERT_OVG_EXT, colormask::r);

            constexpr AdvancedColorBlendAttachmentState blendZeroRg(VK_BLEND_OP_ZERO_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendSrcRg(VK_BLEND_OP_SRC_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDstRg(VK_BLEND_OP_DST_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendSrcOverRg(VK_BLEND_OP_SRC_OVER_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDstOverRg(VK_BLEND_OP_DST_OVER_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendSrcInRg(VK_BLEND_OP_SRC_IN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDstInRg(VK_BLEND_OP_DST_IN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendSrcOutRg(VK_BLEND_OP_SRC_OUT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDstOutRg(VK_BLEND_OP_DST_OUT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendSrcAtopRg(VK_BLEND_OP_SRC_ATOP_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDstAtopRg(VK_BLEND_OP_DST_ATOP_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendXorRg(VK_BLEND_OP_XOR_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendMultiplyRg(VK_BLEND_OP_MULTIPLY_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendScreenRg(VK_BLEND_OP_SCREEN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendOverlayRg(VK_BLEND_OP_OVERLAY_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDarkenRg(VK_BLEND_OP_DARKEN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendLightenRg(VK_BLEND_OP_LIGHTEN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendColorDodgeRg(VK_BLEND_OP_COLORDODGE_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendColorBurnRg(VK_BLEND_OP_COLORBURN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendHardLightRg(VK_BLEND_OP_HARDLIGHT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendSoftLightRg(VK_BLEND_OP_SOFTLIGHT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendDifferenceRg(VK_BLEND_OP_DIFFERENCE_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendExclusionRg(VK_BLEND_OP_EXCLUSION_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendInvertRg(VK_BLEND_OP_INVERT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendInvertRgbRg(VK_BLEND_OP_INVERT_RGB_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendLinearDodgeRg(VK_BLEND_OP_LINEARDODGE_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendLinearBurnRg(VK_BLEND_OP_LINEARBURN_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendVividLightRg(VK_BLEND_OP_VIVIDLIGHT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendLinearLightRg(VK_BLEND_OP_LINEARLIGHT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendPinLightRg(VK_BLEND_OP_PINLIGHT_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendHardMixRg(VK_BLEND_OP_HARDMIX_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendHslHueRg(VK_BLEND_OP_HSL_HUE_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendHslSaturationRg(VK_BLEND_OP_HSL_SATURATION_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendHslColorRg(VK_BLEND_OP_HSL_COLOR_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendHslLuminosityRg(VK_BLEND_OP_HSL_LUMINOSITY_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendPlusRg(VK_BLEND_OP_PLUS_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedRg(VK_BLEND_OP_PLUS_CLAMPED_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedAlphaRg(VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendPlusDarkenRg(VK_BLEND_OP_PLUS_DARKER_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendMinusRg(VK_BLEND_OP_MINUS_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendMinusClampedRg(VK_BLEND_OP_MINUS_CLAMPED_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendContrastRg(VK_BLEND_OP_CONTRAST_EXT, colormask::rg);
            constexpr AdvancedColorBlendAttachmentState blendInvertOvgRg(VK_BLEND_OP_INVERT_OVG_EXT, colormask::rg);

            constexpr AdvancedColorBlendAttachmentState blendZeroRgb(VK_BLEND_OP_ZERO_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendSrcRgb(VK_BLEND_OP_SRC_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDstRgb(VK_BLEND_OP_DST_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendSrcOverRgb(VK_BLEND_OP_SRC_OVER_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDstOverRgb(VK_BLEND_OP_DST_OVER_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendSrcInRgb(VK_BLEND_OP_SRC_IN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDstInRgb(VK_BLEND_OP_DST_IN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendSrcOutRgb(VK_BLEND_OP_SRC_OUT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDstOutRgb(VK_BLEND_OP_DST_OUT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendSrcAtopRgb(VK_BLEND_OP_SRC_ATOP_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDstAtopRgb(VK_BLEND_OP_DST_ATOP_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendXorRgb(VK_BLEND_OP_XOR_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendMultiplyRgb(VK_BLEND_OP_MULTIPLY_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendScreenRgb(VK_BLEND_OP_SCREEN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendOverlayRgb(VK_BLEND_OP_OVERLAY_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDarkenRgb(VK_BLEND_OP_DARKEN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendLightenRgb(VK_BLEND_OP_LIGHTEN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendColorDodgeRgb(VK_BLEND_OP_COLORDODGE_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendColorBurnRgb(VK_BLEND_OP_COLORBURN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendHardLightRgb(VK_BLEND_OP_HARDLIGHT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendSoftLightRgb(VK_BLEND_OP_SOFTLIGHT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendDifferenceRgb(VK_BLEND_OP_DIFFERENCE_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendExclusionRgb(VK_BLEND_OP_EXCLUSION_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendInvertRgb(VK_BLEND_OP_INVERT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendInvertRgbRgb(VK_BLEND_OP_INVERT_RGB_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendLinearDodgeRgb(VK_BLEND_OP_LINEARDODGE_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendLinearBurnRgb(VK_BLEND_OP_LINEARBURN_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendVividLightRgb(VK_BLEND_OP_VIVIDLIGHT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendLinearLightRgb(VK_BLEND_OP_LINEARLIGHT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendPinLightRgb(VK_BLEND_OP_PINLIGHT_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendHardMixRgb(VK_BLEND_OP_HARDMIX_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendHslHueRgb(VK_BLEND_OP_HSL_HUE_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendHslSaturationRgb(VK_BLEND_OP_HSL_SATURATION_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendHslColorRgb(VK_BLEND_OP_HSL_COLOR_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendHslLuminosityRgb(VK_BLEND_OP_HSL_LUMINOSITY_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendPlusRgb(VK_BLEND_OP_PLUS_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedRgb(VK_BLEND_OP_PLUS_CLAMPED_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedAlphaRgb(VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendPlusDarkenRgb(VK_BLEND_OP_PLUS_DARKER_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendMinusRgb(VK_BLEND_OP_MINUS_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendMinusClampedRgb(VK_BLEND_OP_MINUS_CLAMPED_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendContrastRgb(VK_BLEND_OP_CONTRAST_EXT, colormask::rgb);
            constexpr AdvancedColorBlendAttachmentState blendInvertOvgRgb(VK_BLEND_OP_INVERT_OVG_EXT, colormask::rgb);

            constexpr AdvancedColorBlendAttachmentState blendZeroRgba(VK_BLEND_OP_ZERO_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendSrcRgba(VK_BLEND_OP_SRC_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDstRgba(VK_BLEND_OP_DST_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendSrcOverRgba(VK_BLEND_OP_SRC_OVER_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDstOverRgba(VK_BLEND_OP_DST_OVER_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendSrcInRgba(VK_BLEND_OP_SRC_IN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDstInRgba(VK_BLEND_OP_DST_IN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendSrcOutRgba(VK_BLEND_OP_SRC_OUT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDstOutRgba(VK_BLEND_OP_DST_OUT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendSrcAtopRgba(VK_BLEND_OP_SRC_ATOP_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDstAtopRgba(VK_BLEND_OP_DST_ATOP_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendXorRgba(VK_BLEND_OP_XOR_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendMultiplyRgba(VK_BLEND_OP_MULTIPLY_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendScreenRgba(VK_BLEND_OP_SCREEN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendOverlayRgba(VK_BLEND_OP_OVERLAY_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDarkenRgba(VK_BLEND_OP_DARKEN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendLightenRgba(VK_BLEND_OP_LIGHTEN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendColorDodgeRgba(VK_BLEND_OP_COLORDODGE_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendColorBurnRgba(VK_BLEND_OP_COLORBURN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendHardLightRgba(VK_BLEND_OP_HARDLIGHT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendSoftLightRgba(VK_BLEND_OP_SOFTLIGHT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendDifferenceRgba(VK_BLEND_OP_DIFFERENCE_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendExclusionRgba(VK_BLEND_OP_EXCLUSION_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendInvertRgba(VK_BLEND_OP_INVERT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendInvertRgbRgba(VK_BLEND_OP_INVERT_RGB_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendLinearDodgeRgba(VK_BLEND_OP_LINEARDODGE_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendLinearBurnRgba(VK_BLEND_OP_LINEARBURN_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendVividLightRgba(VK_BLEND_OP_VIVIDLIGHT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendLinearLightRgba(VK_BLEND_OP_LINEARLIGHT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendPinLightRgba(VK_BLEND_OP_PINLIGHT_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendHardMixRgba(VK_BLEND_OP_HARDMIX_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendHslHueRgba(VK_BLEND_OP_HSL_HUE_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendHslSaturationRgba(VK_BLEND_OP_HSL_SATURATION_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendHslColorRgba(VK_BLEND_OP_HSL_COLOR_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendHslLuminosityRgba(VK_BLEND_OP_HSL_LUMINOSITY_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendPlusRgba(VK_BLEND_OP_PLUS_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedRgba(VK_BLEND_OP_PLUS_CLAMPED_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendPlusClampedAlphaRgba(VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendPlusDarkenRgba(VK_BLEND_OP_PLUS_DARKER_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendMinusRgba(VK_BLEND_OP_MINUS_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendMinusClampedRgba(VK_BLEND_OP_MINUS_CLAMPED_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendContrastRgba(VK_BLEND_OP_CONTRAST_EXT, colormask::rgba);
            constexpr AdvancedColorBlendAttachmentState blendInvertOvgRgba(VK_BLEND_OP_INVERT_OVG_EXT, colormask::rgba);

            constexpr AdvancedColorBlendAttachmentState blendRed(VK_BLEND_OP_RED_EXT); // (R,G,B,A) = (Rs', Gd, Bd, Ad)
            constexpr AdvancedColorBlendAttachmentState blendGreen(VK_BLEND_OP_GREEN_EXT); // (R,G,B,A) = (Rd, Gs', Bd, Ad)
            constexpr AdvancedColorBlendAttachmentState blendBlue(VK_BLEND_OP_BLUE_EXT); // (R,G,B,A) = (Rd, Gd, Bs', Ad)
        } // namespace advanced
#endif // VK_EXT_blend_operation_advanced
    } // namespace blendstate
} // namespace magma
