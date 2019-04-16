#ifndef FP_INTERFACE_RENDER_H
#define FP_INTERFACE_RENDER_H

#include "FpColorRGB.h"
#include "FpFont.h"
#include "FpGfxTypes.h"
#include <string>

namespace fp
{

class IRender
{
public:
    virtual ~IRender(){}
    virtual void drawPixel( const gfx::Coord&    pixPos,
                            const ColorRGB& colorRGB) = 0;
    virtual void streamToSubWindow(const gfx::Rectangle& subWindow,
                                   const ColorRGB*  pPixelStream) = 0;
    virtual void streamFromFramebuf(const gfx::Rectangle& subWindow,
                                    const gfx::Resolution& resolution,
                                    const ColorRGB*  pFrameBuf) = 0;
    virtual void drawLine(  const gfx::Coord&    p1,
                            const gfx::Coord&    p2,
                            const ColorRGB& colorRGB) = 0;
    virtual void drawHLine( const gfx::Coord&    p1,
                            gfx::Pixel           width,
                            const ColorRGB& colorRGB) = 0;
    virtual void drawVLine( const gfx::Coord&    p1,
                            gfx::Pixel           height,
                            const ColorRGB& colorRGB) = 0;
    virtual void drawRectangle( const gfx::Rectangle& rect,
                                const ColorRGB&  colorRGB,
                                bool                           filled) = 0;
    virtual void drawText(  const gfx::Coord&    textMidLinePos,
                            const ColorRGB& colorRGB,
                            const std::string&            txt) = 0;
    virtual void setFont(const GfxFont& rFont, uint8_t scaleFactor) = 0;
    virtual void getRenderedTextSize(const std::string&      txt,
                                     const GfxFont*          pFont,
                                     gfx::Size2D&   size,
                                     gfx::Offset2D& offset) = 0;
    virtual gfx::Resolution getResolution() const = 0;
};

} // namespace fp
#endif