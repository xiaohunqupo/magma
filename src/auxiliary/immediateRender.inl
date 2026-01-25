namespace magma::aux
{
inline void ImmediateRender::setVertexShader(const VertexShaderStage& shader) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    shaderStages.front() = shader;
}

inline void ImmediateRender::setFragmentShader(const FragmentShaderStage& shader) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    shaderStages.back() = shader;
}

inline void ImmediateRender::setRasterizationState(const RasterizationState& state) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    rasterizationState = state;
#ifdef VK_EXT_line_rasterization
    auto lineRasterizationInfo = rasterizationState.findNode<VkPipelineRasterizationLineStateCreateInfoEXT>(
        VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_LINE_STATE_CREATE_INFO_EXT);
    if (lineRasterizationInfo)
        stippledLineState = lineRasterizationInfo->stippledLineEnable;
#endif // VK_EXT_line_rasterization
}

inline void ImmediateRender::setMultisampleState(const MultisampleState& state) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    multisampleState = state;
}

inline void ImmediateRender::setDepthStencilState(const DepthStencilState& state) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    depthStencilState = state;
}

inline void ImmediateRender::setColorBlendState(const ColorBlendState& state) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    colorBlendState = MultiColorBlendState(state); // Make copyable
}

inline bool ImmediateRender::setLineWidth(float width) noexcept
{
    MAGMA_ASSERT(wideLinesEnabled);
    if (!wideLinesEnabled)
        return false;
    MAGMA_ASSERT(!insidePrimitive);
    MAGMA_ASSERT(width >= lineWidthRange[0]);
    MAGMA_ASSERT(width <= lineWidthRange[1]);
    width = alignByGranularity(width, lineWidthRange[0], lineWidthGranularity);
    lineWidth = std::clamp(width, lineWidthRange[0], lineWidthRange[1]);
    return true;
}

inline void ImmediateRender::setLineStippleFactor(uint32_t stippleFactor) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    lineStippleFactor = stippleFactor;
}

inline void ImmediateRender::setLineStipplePattern(uint16_t stipplePattern) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    lineStipplePattern = stipplePattern;
}

inline void ImmediateRender::setIdentity() noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    constexpr float identity[4][4] = {
        {1.f, 0.f, 0.f, 0.f},
        {0.f, 1.f, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 1.f}};
    memcpy(world, identity, sizeof(identity));
}

inline void ImmediateRender::setTransform(const float matrix[4][4]) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    memcpy(world, matrix, sizeof(world));
}

inline void ImmediateRender::setViewProjTransform(const float matrix[4][4]) noexcept
{
    MAGMA_ASSERT(!insidePrimitive);
    memcpy(viewProj, matrix, sizeof(viewProj));
}

inline void ImmediateRender::normal(float x, float y, float z) noexcept
{
    v->normalPSize.v[0] = x;
    v->normalPSize.v[1] = y;
    v->normalPSize.v[2] = z;
}

inline void ImmediateRender::normal(const float n[3]) noexcept
{
    normal(n[0], n[1], n[2]);
}

inline void ImmediateRender::color(float r, float g, float b, float a /* 1 */) noexcept
{
    v->color.v[0] = r;
    v->color.v[1] = g;
    v->color.v[2] = b;
    v->color.v[3] = a;
}

inline void ImmediateRender::color(const float c[4]) noexcept
{
    color(c[0], c[1], c[2], c[3]);
}

inline void ImmediateRender::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a /* std::numeric_limits<uint8_t>::max() */) noexcept
{
    color(r/255.f, g/255.f, b/255.f, a/255.f);
}

inline void ImmediateRender::color(const uint8_t c[4]) noexcept
{
    color(c[0], c[1], c[2], c[3]);
}

inline void ImmediateRender::texCoord(float s, float t) noexcept
{
    v->texCoord.v[0] = s;
    v->texCoord.v[1] = t;
}

inline void ImmediateRender::texCoord(const float uv[2]) noexcept
{
    texCoord(uv[0], uv[1]);
}

inline bool ImmediateRender::pointSize(float size) noexcept
{
    MAGMA_ASSERT(largePointsEnabled);
    if (!largePointsEnabled)
        return false;
    MAGMA_ASSERT(size >= pointSizeRange[0]);
    MAGMA_ASSERT(size <= pointSizeRange[1]);
    size = alignByGranularity(size, pointSizeRange[0], pointSizeGranularity);
    v->normalPSize.v[3] = std::clamp(size, pointSizeRange[0], pointSizeRange[1]);
    return true;
}

inline void ImmediateRender::vertex(float x, float y, float z /* 0 */, float w /* 1 */) noexcept
{
    MAGMA_ASSERT(insidePrimitive);
    MAGMA_ASSERT(vertexCount < maxVertexCount);
    if (insidePrimitive && vertexCount < maxVertexCount)
    {
        v->position.v[0] = x;
        v->position.v[1] = y;
        v->position.v[2] = z;
        v->position.v[3] = w;
        // Propagate v state to the next vertex
        const Vertex *last = v;
        *++v = *last;
        ++primitives.back().vertexCount;
        ++vertexCount;
    }
}

inline void ImmediateRender::vertex(const float v[4]) noexcept
{
    vertex(v[0], v[1], v[2], v[3]);
}

inline float ImmediateRender::alignByGranularity(float value, float minRange, float granularity) const noexcept
{
    MAGMA_ASSERT(granularity > 0.f);
    const float steps = (value - minRange) / granularity;
    const float roundedSteps = roundf(steps);
    const bool aligned = fabsf(steps - roundedSteps) < 1e-6f;
    MAGMA_ASSERT(aligned);
    if (!aligned)
        value = minRange + roundedSteps * granularity;
    return value;
}
} // namespace magma::aux
