#include "FpColorRGB.h"
#include <algorithm> //std::min

static const uint8_t ditherThresholdR[64] = {
    1, 7, 3, 5, 0, 8, 2, 6,
    7, 1, 5, 3, 8, 0, 6, 2,
    3, 5, 0, 8, 2, 6, 1, 7,
    5, 3, 8, 0, 6, 2, 7, 1,

    0, 8, 2, 6, 1, 7, 3, 5,
    8, 0, 6, 2, 7, 1, 5, 3,
    2, 6, 1, 7, 3, 5, 0, 8,
    6, 2, 7, 1, 5, 3, 8, 0
};

static const uint8_t ditherThresholdG[64] = {
    1, 3, 2, 2, 3, 1, 2, 2,
    2, 2, 0, 4, 2, 2, 4, 0,
    3, 1, 2, 2, 1, 3, 2, 2,
    2, 2, 4, 0, 2, 2, 0, 4,

    1, 3, 2, 2, 3, 1, 2, 2,
    2, 2, 0, 4, 2, 2, 4, 0,
    3, 1, 2, 2, 1, 3, 2, 2,
    2, 2, 4, 0, 2, 2, 0, 4
};

static const uint8_t ditherThresholdB[64] = {
    5, 3, 8, 0, 6, 2, 7, 1,
    3, 5, 0, 8, 2, 6, 1, 7,
    8, 0, 6, 2, 7, 1, 5, 3,
    0, 8, 2, 6, 1, 7, 3, 5,

    6, 2, 7, 1, 5, 3, 8, 0,
    2, 6, 1, 7, 3, 5, 0, 8,
    7, 1, 5, 3, 8, 0, 6, 2,
    1, 7, 3, 5, 0, 8, 2, 6
};

template<typename ColorRepr>
constexpr uint16_t fp::detail::color::ColorRGB<ColorRepr>::toUint16_BRG565_dither(uint32_t x, uint32_t y) const noexcept
{
    const uint8_t thresholdIndex = ((y & 7) << 3) + (x & 7);
    uint8_t r = std::min(m_colorRepr.r() + ditherThresholdR[thresholdIndex], 255) >> 3 << 3;
    uint8_t g = std::min(m_colorRepr.g() + ditherThresholdG[thresholdIndex], 255) >> 2 << 2;
    uint8_t b = std::min(m_colorRepr.b() + ditherThresholdB[thresholdIndex], 255) >> 3 << 3;
    return ((b >> 3) << 11) | ((g >> 2) << 5) | (r >> 3);
}