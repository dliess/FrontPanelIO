#ifndef COLOR_RGB_H
#define COLOR_RGB_H

#include <cstdint>

namespace fp
{

using ColorRGB16 = uint16_t;

struct ColorRGB
{
    ColorRGB() : m_rgb(0xff000000){}
    ColorRGB(uint32_t r, uint32_t g, uint32_t b) :
        m_rgb(  (b & 0xff) <<  0 | 
                (g & 0xff) <<  8 | 
                (r & 0xff) << 16 |
                0xff000000 )
        {}
    uint32_t toUint32_0xffRRGGBB() const
    {
        return m_rgb;
    }
    uint32_t toUint32_0xRRGGBBff() const
    {
        return (m_rgb << 8) | 0x000000ff;
    }
    uint16_t toUint16_BRG565(uint32_t x, uint32_t y) const;
    bool operator!=(const ColorRGB& rhs) const
    {
        return m_rgb != rhs.m_rgb;
    }
    uint8_t r() const { return (m_rgb >> 16) & 0xff; }
    uint8_t g() const { return (m_rgb >>  8) & 0xff; }
    uint8_t b() const { return (m_rgb      ) & 0xff; }
private:
    uint32_t m_rgb; //0xffRRGGBB
};

} // namespace fp
#endif