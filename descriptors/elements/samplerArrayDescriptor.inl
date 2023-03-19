namespace magma
{
namespace descriptor
{
class DescriptorArray::ImmutableSamplerDescriptor
{
protected:
    VkSampler& immutableSampler;
    bool& updated;

public:
    explicit ImmutableSamplerDescriptor(VkSampler& immutableSampler, bool& updated) noexcept:
        immutableSampler(immutableSampler),
        updated(updated)
    {}

    void operator=(std::shared_ptr<const magma::Sampler> sampler) noexcept
    {
        MAGMA_ASSERT(sampler);
        MAGMA_ASSERT(VK_NULL_HANDLE == immutableSampler);
        if (VK_NULL_HANDLE == immutableSampler) // Immutable sampler must be updated only once
        {
            immutableSampler = *sampler;
            updated = true;
        }
    }
};

class DescriptorArray::ImageImmutableSamplerDescriptor :
    public DescriptorArray::ImmutableSamplerDescriptor
{
    VkDescriptorImageInfo& descriptor;
    VkImageType& imageType;

public:
    explicit ImageImmutableSamplerDescriptor(VkDescriptorImageInfo& descriptor, VkSampler& immutableSampler, VkImageType& imageType, bool& updated) noexcept:
        ImmutableSamplerDescriptor(immutableSampler, updated),
        descriptor(descriptor),
        imageType(imageType)
    {}

    void operator=(const std::pair<std::shared_ptr<const ImageView>, std::shared_ptr<const magma::Sampler>>& combinedImageSampler) noexcept
    {
        MAGMA_ASSERT(combinedImageSampler.first);
        MAGMA_ASSERT(combinedImageSampler.second);
        std::shared_ptr<const Image> image = combinedImageSampler.first->getImage();
        MAGMA_ASSERT(image->getUsage() & VK_IMAGE_USAGE_SAMPLED_BIT);
        if (descriptor.imageView != *combinedImageSampler.first)
        {
            descriptor = combinedImageSampler.first->getDescriptor(nullptr);
            if (imageType != VK_IMAGE_TYPE_MAX_ENUM)
                MAGMA_ASSERT(image->getType() == imageType);
            imageType = image->getType();
            updated = true;
        }
        ImmutableSamplerDescriptor::operator=(combinedImageSampler.second);
    }

    void operator=(std::shared_ptr<const ImageView> imageView) noexcept
    {
        MAGMA_ASSERT(imageView);
        std::shared_ptr<const Image> image = imageView->getImage();
        MAGMA_ASSERT(image->getUsage() & VK_IMAGE_USAGE_SAMPLED_BIT);
        MAGMA_ASSERT(immutableSampler != VK_NULL_HANDLE); // Check that sampler is already set and stop carrying around it
        if (descriptor.imageView != *imageView)
        {
            descriptor = imageView->getDescriptor(nullptr);
            if (imageType != VK_IMAGE_TYPE_MAX_ENUM)
                MAGMA_ASSERT(image->getType() == imageType);
            imageType = image->getType();
            updated = true;
        }
    }
};
} // namespace descriptor
} // namespace magma
