/*
Magma - abstraction layer to facilitate usage of Khronos Vulkan API.
Copyright (C) 2018-2020 Victor Coda.

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
#include "swapchainFramebuffer.h"
#include "../objects/device.h"
#include "../objects/image2DAttachment.h"
#include "../objects/imageView.h"
#include "../objects/renderPass.h"
#include "../objects/framebuffer.h"

namespace magma
{
namespace aux
{
SwapchainFramebuffer::SwapchainFramebuffer(std::shared_ptr<SwapchainColorAttachment> color,
    VkFormat depthFormat /* VK_FORMAT_UNDEFINED */,
    const VkComponentMapping& swizzle /* VK_COMPONENT_SWIZZLE_IDENTITY */,
    std::shared_ptr<IAllocator> allocator /* nullptr */):
    Framebuffer(1)
{
    std::shared_ptr<Device> device = color->getDevice();
    colorView = std::make_shared<ImageView>(color, swizzle, allocator);
    std::vector<std::shared_ptr<ImageView>> attachments;
    attachments.push_back(colorView);
    if (depthFormat != VK_FORMAT_UNDEFINED)
    {
        const VkExtent2D extent{color->getMipExtent(0).width, color->getMipExtent(0).height};
        depthStencil = std::make_shared<DepthStencilAttachment>(device, depthFormat, extent, 1, color->getSamples(), false, allocator);
        depthStencilView = std::make_shared<ImageView>(depthStencil, swizzle, allocator);
        attachments.push_back(depthStencilView);
    }
    const AttachmentDescription colorAttachment(color->getFormat(), 1,
        op::clearStore, // Clear color, store
        op::dontCare, // Stencil don't care
        VK_IMAGE_LAYOUT_UNDEFINED,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    if (depthFormat != VK_FORMAT_UNDEFINED)
    {
        const AttachmentDescription depthStencilAttachment(depthFormat, 1,
            op::clearStore, // Clear depth, store
            op::clearDontCare, // Stencil don't care
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
        renderPass = std::make_shared<RenderPass>(device, std::initializer_list<AttachmentDescription>{
            colorAttachment, depthStencilAttachment}, allocator);
    }
    else
    {
        renderPass = std::make_shared<RenderPass>(device, colorAttachment, allocator);
    }
    framebuffer = std::make_shared<magma::Framebuffer>(renderPass, attachments, 0, allocator);
}
} // namespace aux
} // namespace magma