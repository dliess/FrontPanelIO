#ifndef FP_LED_H
#define FP_LED_H

#include <cstdint>

namespace fp
{
    struct Widget;
}

namespace fp
{
    
class Led
{
public:
    struct ColorRGB
    {
        uint32_t r;
        uint32_t g;
        uint32_t b;
    };
    enum ColorIndex
    {
        White = 0,
        Black,
        Red,
        DarkRed,
        Green,
        DarkGreen,
        Blue,
        DarkBlue,
        Cyan,
        DarkCyan,
        Magenta,
        DarkMagenta,
        Yellow,
        DarkYellow,
        Gray,
        DarkGray,
        LightGray,
        Last = LightGray
    };
    static const ColorRGB& getRGB(ColorIndex colorIdx)
    {
       static const ColorRGB colorMap[ColorIndex::Last + 1] = { {0xff, 0xff, 0xff},   // White
                                                                {0x00, 0x00, 0x00},   // Black
                                                                {0xff, 0x00, 0x00},   // Red
                                                                {0x80, 0x00, 0x00},   // DarkRed
                                                                {0x00, 0xff, 0x00},   // Green
                                                                {0x00, 0x80, 0x00},   // Dark Green
                                                                {0x00, 0x00, 0xff},   // Blue
                                                                {0x00, 0x00, 0x80},   // DarkBlue
                                                                {0x00, 0xff, 0xff},   // Cyan
                                                                {0x00, 0x80, 0x80},   // DarkCyan
                                                                {0xff, 0x00, 0xff},   // Magenta
                                                                {0x80, 0x00, 0x80},   // Dark Magenta
                                                                {0xff, 0xff, 0x00},   // Yellow
                                                                {0x80, 0x80, 0x00},   // DarkYellow
                                                                {0xa0, 0xa0, 0xa4},   // Gray
                                                                {0x80, 0x80, 0x80},   // DarkGrey
                                                                {0xc0, 0xc0, 0xc0} }; // LightGray
       return colorMap[colorIdx];
    }
    class ISetter
    {
    public:
        virtual void setLed(const Widget& w, const fp::Led::ColorRGB& colorRGB) = 0;
    };
    class ILedScene
    {
    public:
        virtual void onGotRevealed(const Widget& w) = 0;
        virtual void onGotHidden(const Widget& w) = 0;
    };
};

} // namespace fp
#endif