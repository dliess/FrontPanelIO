#ifndef FP_RENDER_BASE_H
#define FP_RENDER_BASE_H

#include "FpIRender.h"
#include "FpFontRenderer.h"

namespace fp
{

class RenderBase : public IRender
{
public:
    RenderBase();
    virtual ~RenderBase(){}
    virtual void streamToSubWindow(const gfx::Rectangle& subWindow,
                                     const ColorRGB*  pPixelStream) override;
    virtual void streamFromFramebuf(const gfx::Rectangle& subWindow,
                                    const gfx::Resolution& resolution,
                                    const ColorRGB*  pFrameBuf) override;
    virtual void drawLine(  const gfx::Coord&    p1,
                            const gfx::Coord&    p2,
                            const ColorRGB& colorRGB) override;
    virtual void drawHLine( const gfx::Coord&    p1,
                            gfx::Pixel           width,
                            const ColorRGB& colorRGB) override;
    virtual void drawVLine( const gfx::Coord&    p1,
                            gfx::Pixel           height,
                            const ColorRGB& colorRGB) override;
    virtual void drawRectangle( const gfx::Rectangle& rect,
                                const ColorRGB&  colorRGB,
                                bool             filled) override;
    virtual void drawText(  const gfx::Coord&    textMidLinePos,
                            const ColorRGB& colorRGB,
                            const std::string&            str) override;
    virtual void setFont(const GfxFont& rFont, uint8_t scaleFactor) override;
    virtual void getRenderedTextSize(const std::string&      txt,
                                     const GfxFont*          pFont,
                                     gfx::Size2D&   size,
                                     gfx::Offset2D& offset) override;
private:
    void _drawLine( const gfx::Coord&    p1,
                    const gfx::Coord&    p2,
                    const ColorRGB& colorRGB);
    FontRenderer m_fontRenderer;
};

} // namespace fp
#endif