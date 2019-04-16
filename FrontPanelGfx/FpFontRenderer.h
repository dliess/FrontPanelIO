#ifndef FP_FONT_RENDERER_H
#define FP_FONT_RENDERER_H

#include "FpFont.h"
#include "FpGfxTypes.h"
#include "FpColorRGB.h"
#include <string>

namespace fp
{
class IRender;
}

namespace fp
{

class FontRenderer
{
public:
    FontRenderer(IRender& rRenderIf);
    void drawText(  const gfx::Coord&    textMidLinePos,
                    const ColorRGB& colorRGB,
                    const std::string&            str);
    void setFont(const GfxFont& rFont, uint8_t scaleFactor);
    void getRenderedTextSize(const std::string&      txt,
                             const GfxFont*          pFont,
                             gfx::Size2D&   size,
                             gfx::Offset2D& offset);
private:
    IRender&       m_rRenderIf;
    const GfxFont*  m_pFont;
    uint8_t         m_scaleFactor;
    void drawChar(const gfx::Coord&    pixelPos,
                  const ColorRGB& colorRGB,
                  unsigned char c);
    void drawCharFixedSize(const gfx::Coord&     pixelPos,
                           const ColorRGB&  colorRGB,
                           unsigned char                  c,
                           bool                           clearBackground);
    void drawCharProportional(const gfx::Coord&    pixelPos,
                         const ColorRGB& colorRGB,
                         unsigned char c);
    void drawPixel(const gfx::Coord&     charBase,
                   const gfx::Offset2D&  offset,
                   const ColorRGB&  colorRGB);

};

} // namespace fp
#endif