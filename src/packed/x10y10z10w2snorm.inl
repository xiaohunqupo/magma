namespace magma::packed
{
inline X10y10z10w2Snorm::X10y10z10w2Snorm(float x, float y, float z, int32_t w /* 0 */) noexcept
{
#ifdef MAGMA_SSE
    __m128 v = _mm_set_ps(float(w), z, y, x);
    v = _mm_max_ps(v, _mm_set_ps1(-1.f));
    v = _mm_min_ps(v, _mm_set_ps1(1.f));
    __m128 scale = _mm_set_ps(1.f, 511.f, 511.f, 511.f);
    v = _mm_mul_ps(v, scale);
    v = _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    __m128 bitshift = _mm_set_ps(1024.f * 1024.f * 1024.f, 1024.f * 1024.f, 1024.f, 1.f);
    v = _mm_mul_ps(v, bitshift);
    __m128i iv = _mm_cvtps_epi32(v);
    // mask off any fraction
    __m128i mask = _mm_set_epi32(0xC0000000, 0x3FF << 20, 0x3FF << 10, 0x3FF);
    iv = _mm_and_si128(iv, mask);
    iv = _mm_horizontal_or(iv);
    this->v = _mm_cvtsi128_si32(iv);
#elif defined(MAGMA_NEON)
    float32x4_t v = {x, y, z, float(w)};
    v = vmaxq_f32(v, vdupq_n_f32(-1.f));
    v = vminq_f32(v, vdupq_n_f32(1.f));
    float32x4_t scale = {511.f, 511.f, 511.f, 1.f};
    v = vmulq_f32(v, scale);
    int32x4_t iv = vcvtnq_s32_f32(v);
    // mask off any fraction
    int32x4_t mask = {0x3FF, 0x3FF, 0x3FF, 0x3};
    iv = vandq_s32(iv, mask);
    int32x4_t bitshift = {0, 10, 20, 30};
    iv = vshlq_s32(iv, bitshift);
    int32x2_t ored = vhorizontal_or(iv);
    this->v = vget_lane_s32(ored, 0);
#else // FPU
    x = std::clamp(x, -1.f, 1.f);
    y = std::clamp(y, -1.f, 1.f);
    z = std::clamp(z, -1.f, 1.f);
    w = std::clamp(w, -1, 1);
    x = std::roundf(x * 511.f);
    y = std::roundf(y * 511.f);
    z = std::roundf(z * 511.f);
    this->x = int32_t(x) & 0x3FF;
    this->y = int32_t(y) & 0x3FF;
    this->z = int32_t(z) & 0x3FF;
    this->w = w & 0x3;
#endif // FPU
}
} // namespace magma::packed
