constexpr StreamRasterizationState::StreamRasterizationState(const RasterizationState& state, uint32_t rasterizationStream,
    VkPipelineRasterizationStateStreamCreateFlagsEXT flags /* 0 */) noexcept:
    RasterizationState(state),
    stream{
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_STREAM_CREATE_INFO_EXT,
        state.pNext,
        flags,
        rasterizationStream
    }
{
    pNext = &stream;
}

inline std::size_t StreamRasterizationState::hash() const noexcept
{
    std::size_t hash = RasterizationState::hash();
    core::hashCombine(hash, core::hashArgs(
        stream.sType,
        stream.flags,
        stream.rasterizationStream));
    return hash;
}

constexpr bool StreamRasterizationState::operator==(const StreamRasterizationState& other) const noexcept
{
    return RasterizationState::operator==(other) &&
        (stream.flags == other.stream.flags) &&
        (stream.rasterizationStream == other.stream.rasterizationStream);
}
