#include "FpFontRenderer.h"
#include "FpGfxTypes.h"
#include "FpIRender.h"
#include "DefaultMonospace.h"
#include <string>

using namespace fp;

FontRenderer::FontRenderer(IRender& rRenderIf) :
    m_rRenderIf(rRenderIf),
    m_pFont(&DefaultMonospace),
    m_scaleFactor(1)
    {}


void FontRenderer::drawText(const gfx::Coord&    textMidLinePos,
                            const ColorRGB& colorRGB,
                            const std::string&            str)
{
    gfx::Coord charMidLinePos(textMidLinePos);
    for(const char& c : str)
    {
        drawChar(charMidLinePos, colorRGB, c);
        charMidLinePos.x += m_pFont->getAdvance(c).x * m_scaleFactor;
    }
}

void FontRenderer::setFont(const GfxFont& rFont, uint8_t scaleFactor)
{
    m_pFont = &rFont;
    m_scaleFactor = scaleFactor;
}

void FontRenderer::getRenderedTextSize(const std::string&      txt,
                                       const GfxFont*          pFont,
                                       gfx::Size2D&   size,
                                       gfx::Offset2D& offset)
{
    if(0 == txt.size())
    {
        return;
    }
    const GfxFont* pFontToUse = (nullptr == pFont) ? m_pFont : pFont;
    offset = m_pFont->getOffset(txt.front());

    switch(pFontToUse->getType())
    {
        case GfxFont::MONOSPACED:
        {
            size.h = pFontToUse->getSize().h;
            size.w = pFontToUse->getAdvance().x * txt.size();
            break;
        }
        case GfxFont::PROPORTIONAL:
        default:
        {
            int32_t yMin =  10000;
            int32_t yMax = -10000;
            for(const char& c : txt)
            {
                const int32_t yOffs = pFontToUse->getOffset(c).y;
                yMin = std::min(yMin, yOffs);
                yMax = std::max(yMax, yOffs + static_cast<int32_t>(m_pFont->getSize(c).h) - 1);
                size.w += pFontToUse->getAdvance(c).x;
            }
            size.h = (yMax - yMin + 1);
            offset.y = yMin;
            break;
        }
    }

    const gfx::Pixel endCharWidth = pFontToUse->getSize(txt.back()).w + pFontToUse->getOffset(txt.back()).x;
    const gfx::Pixel endCut = pFontToUse->getAdvance(txt.back()).x - endCharWidth;
    const gfx::Pixel startCut = pFontToUse->getOffset(txt.front()).x;

    size.w -= (startCut + endCut);

    size   = size   * m_scaleFactor;
    offset = offset * m_scaleFactor;
}

void FontRenderer::drawChar(const gfx::Coord&    charPos,
                            const ColorRGB& colorRGB,
                            unsigned char c)
{
    switch(m_pFont->getType())
    {
        case GfxFont::MONOSPACED:
            drawCharFixedSize(charPos, colorRGB, c, false);
            break;
        case GfxFont::PROPORTIONAL:
        default:
            drawCharProportional(charPos, colorRGB, c);
            break;
    }
}

void FontRenderer::drawPixel(const gfx::Coord&     charBase,
                             const gfx::Offset2D&  offset,
                             const ColorRGB&  colorRGB)
{
    if(1 == m_scaleFactor)
    {
        m_rRenderIf.drawPixel(charBase + offset, colorRGB);
    }
    else
    {
        const auto upperLeft = gfx::Coord(charBase + (offset * m_scaleFactor));
        const auto size = gfx::Size2D(m_scaleFactor, m_scaleFactor);
        const auto rect = gfx::Rectangle(upperLeft, size);
        m_rRenderIf.drawRectangle(rect, colorRGB, true);
    }

}

void FontRenderer::drawCharFixedSize(const gfx::Coord&     midLinePos,
                                     const ColorRGB&  colorRGB,
                                     unsigned char                  c,
                                     bool                           clearBackground)
{   
    const gfx::Coord charUpLeftPos = midLinePos + m_pFont->getOffset(c);

    /* TODO */
    static const ColorRGB backgroungColor(0,0,0);
    /* ---- */
    const auto fontSize = m_pFont->getSize(c);
    for(gfx::Pixel x = 0; x < fontSize.w; x++)
    {
        uint8_t vLine = (m_pFont->getPixMapStart(c))[x];
        for(int8_t y = 0; y < fontSize.h; y++, vLine >>= 1)
        {
            const auto index = gfx::Offset2D(x, y);
            if(vLine & 1)
            {
                drawPixel(charUpLeftPos, index, colorRGB);
            }
            else if(clearBackground && (backgroungColor != colorRGB))
            {
                drawPixel(charUpLeftPos, index, backgroungColor);
            }
        }
    }
    if(backgroungColor != colorRGB)
    {
        if(1 == m_scaleFactor)
        {
            const auto p = gfx::Coord(charUpLeftPos.x + fontSize.w, charUpLeftPos.y);
            m_rRenderIf.drawVLine(p, fontSize.h, backgroungColor);
        }
        else
        {
            const auto upperLeft = gfx::Coord(charUpLeftPos.x + fontSize.w * m_scaleFactor,
                                                       charUpLeftPos.y);
            const auto size = gfx::Size2D(m_scaleFactor, fontSize.h * m_scaleFactor);
            const auto rect = gfx::Rectangle(upperLeft, size);
            m_rRenderIf.drawRectangle(rect, backgroungColor, true);
        }          
    }
}

void FontRenderer::drawCharProportional(const gfx::Coord&    midLinePos,
                                        const ColorRGB& colorRGB,
                                        unsigned char c)
{
    const auto fontOffset = m_pFont->getOffset(c);
    const auto size   = m_pFont->getSize(c);

    //m_rRenderIf.drawLine(midLinePos, midLinePos + (fontOffset * m_scaleFactor), {0,255,0});
    //m_rRenderIf.drawRectangle({midLinePos + (fontOffset * m_scaleFactor), size }, {0,255,0}, false );

    uint8_t  bit = 0;
    uint8_t* pPixMapStartForChar = m_pFont->getPixMapStart(c);
    uint8_t  hLine = 0;

    for(gfx::Pixel y = 0; y < size.h; y++)
    {
        for(gfx::Pixel x = 0; x < size.w; x++)
        {
            if( 0 == bit % 8 )
            {
                hLine = pPixMapStartForChar[bit / 8];
            }
            if(hLine & 0x80)
            {
                const auto index = gfx::Offset2D(x, y);
                gfx::Coord coord(midLinePos);
                drawPixel(coord, fontOffset + index, colorRGB);
            }
            hLine <<= 1;
            bit++;
        }
    }
}

