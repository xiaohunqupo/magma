namespace magma::packed
{
inline R5g5b5a1Unorm::R5g5b5a1Unorm(float r, float g, float b, float a) noexcept
{
#ifdef MAGMA_SSE
    __m128 v = _mm_set_ps(r, g, b, a);
    v = _mm_max_ps(v, _mm_setzero_ps());
    v = _mm_min_ps(v, _mm_set_ps1(1.f));
    v = _mm_mul_ps(v, _mm_set_ps(31.f, 31.f, 31.f, 1.f));
    v = _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    __m128 bitshift = _mm_set_ps(2048.f, 64.f, 2.f, 1.f); // 11, 6, 1, 0
    v = _mm_mul_ps(v, bitshift);
    __m128i iv = _mm_cvtps_epi32(v);
    iv = _mm_horizontal_or(iv);
    this->v = (uint16_t)_mm_extract_epi16(iv, 0);
#elif defined(MAGMA_NEON)
    float32x4_t v = {r, g, b, a};
    v = vmaxq_f32(v, vdupq_n_f32(0.f));
    v = vminq_f32(v, vdupq_n_f32(1.f));
    float32x4_t scale = {31.f, 31.f, 31.f, 1.f};
    v = vmulq_f32(v, scale);
    v = vrndnq_f32(v);
    uint32x4_t iv = vcvtnq_u32_f32(v);
    this->v =
        (((uint16_t)vgetq_lane_u32(iv, 0) & 0x1F) << 11) |
        (((uint16_t)vgetq_lane_u32(iv, 1) & 0x1F) << 6) |
        (((uint16_t)vgetq_lane_u32(iv, 2) & 0x1F) << 1) |
        ((uint16_t)vgetq_lane_u32(iv, 3) & 0x1);
#else // FPU
    r = std::min(std::max(0.f, r), 1.f);
    g = std::min(std::max(0.f, g), 1.f);
    b = std::min(std::max(0.f, b), 1.f);
    a = std::min(std::max(0.f, a), 1.f);
    r = std::roundf(r * 31.f);
    g = std::roundf(g * 31.f);
    b = std::roundf(b * 31.f);
    this->a = uint16_t(a) & 0x1;
    this->b = uint16_t(b) & 0x1F;
    this->g = uint16_t(g) & 0x1F;
    this->r = uint16_t(r) & 0x1F;
#endif // FPU
}

inline R5g5b5a1Unorm::R5g5b5a1Unorm(uint8_t r, uint8_t g, uint8_t b, uint8_t a) noexcept:
    R5g5b5a1Unorm(r/255.f, g/255.f, b/255.f, a/255.f)
{}

inline R5g5b5a1Unorm::R5g5b5a1Unorm(const float v[4]) noexcept:
    R5g5b5a1Unorm(v[0], v[1], v[2], v[3])
{}

inline R5g5b5a1Unorm::R5g5b5a1Unorm(const uint8_t v[4]) noexcept:
    R5g5b5a1Unorm(v[0]/255.f, v[1]/255.f, v[2]/255.f, v[3]/255.f)
{}
} // namespace magma::packed
