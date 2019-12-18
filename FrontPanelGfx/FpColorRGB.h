#ifndef COLOR_RGB_H
#define COLOR_RGB_H

#include <cstdint>

namespace fp
{

using ColorRGB16 = uint16_t;


namespace detail::color
{

class ARGB
{
public:
    constexpr ARGB() noexcept: data(0xff000000) {}
    constexpr ARGB(uint32_t r, uint32_t g, uint32_t b) noexcept:
        data(  (b & 0xff) <<  0 | 
               (g & 0xff) <<  8 | 
               (r & 0xff) << 16 |
               0xff000000 )
        {}
    constexpr uint8_t r() const noexcept{ return (data >> 16) & 0xff; }
    constexpr uint8_t g() const noexcept{ return (data >>  8) & 0xff; }
    constexpr uint8_t b() const noexcept{ return (data      ) & 0xff; }
    constexpr bool operator!=(const ARGB& rhs) const noexcept { return data != rhs.data;}
private:
    uint32_t data;
};

class BGRA
{
public:
    constexpr BGRA() noexcept: data(0x000000ff) {}
    constexpr BGRA(uint32_t r, uint32_t g, uint32_t b) noexcept: 
        data(  (b & 0xff) <<  24 | 
               (g & 0xff) <<  16 | 
               (r & 0xff) <<  8  |
               0x000000ff )
        {}
    constexpr uint8_t r() const noexcept{ return (data >>  8) & 0xff; }
    constexpr uint8_t g() const noexcept{ return (data >> 16) & 0xff; }
    constexpr uint8_t b() const noexcept{ return (data >> 24) & 0xff; }
    constexpr bool operator!=(const BGRA& rhs) const noexcept { return data != rhs.data;}
private:
    uint32_t data;
};


template<typename ColorRepr>
struct ColorRGB
{
    constexpr ColorRGB() noexcept: m_colorRepr() {}
    constexpr ColorRGB(uint32_t r, uint32_t g, uint32_t b) noexcept: m_colorRepr(r, g, b) {}
    constexpr uint32_t toUint32_0xffRRGGBB() const noexcept
    {
        return 0xff000000 | (r() << 16) | (g() << 8) | b();
    }
    constexpr uint32_t toUint32_0xRRGGBBff() const noexcept
    {
        return 0x000000ff | (r() << 24) | (g() << 16) | (b() << 8);
    }
    constexpr uint16_t toUint16_BRG565_dither(uint32_t x, uint32_t y) const noexcept;
    constexpr uint16_t toUint16_BRG565() const noexcept
    {
        return ((b() >> 3) << 11) | ((g() >> 2) << 5) | (r() >> 3);
    }
    constexpr bool operator!=(const ColorRGB& rhs) const noexcept
    {
        return m_colorRepr != rhs.m_colorRepr;
    }
    constexpr uint8_t r() const noexcept{ return m_colorRepr.r(); }
    constexpr uint8_t g() const noexcept{ return m_colorRepr.g(); }
    constexpr uint8_t b() const noexcept{ return m_colorRepr.b(); }
private:
    ColorRepr m_colorRepr;
};

} // namespace detail::color

#ifdef __FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__
using ColorRGB = detail::color::ColorRGB<detail::color::BGRA>;
#else
using ColorRGB = detail::color::ColorRGB<detail::color::ARGB>;
#endif

} // namespace fp

#include "FpColorRGB.tcc"

#endif