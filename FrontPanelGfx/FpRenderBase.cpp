#include "FpRenderBase.h"
#include <cmath>
#include <iostream> //TODO: remove later

using namespace fp;

RenderBase::RenderBase() :
    m_fontRenderer(*this)
    {}

void RenderBase::streamToSubWindow(const gfx::Rectangle& subWindow,
                                   const ColorRGB*  pPixelStream)
{
    for(gfx::Pixel subY = 0; subY < subWindow.height(); ++subY)
    {
        for(gfx::Pixel subX = 0; subX < subWindow.width(); ++subX)
        {
            drawPixel(subWindow.upperLeft + gfx::Coord(subX, subY), pPixelStream[subX + (subY * subWindow.width())]);
        }
    }
}

void RenderBase::streamFromFramebuf(const gfx::Rectangle&  subWindow,
                                    const gfx::Resolution& resolution,
                                    const ColorRGB*        pFrameBuf)
{
    for(gfx::Pixel subY = 0; subY < subWindow.height(); ++subY)
    {
        for(gfx::Pixel subX = 0; subX < subWindow.width(); ++subX)
        {
            const gfx::Coord pixCoord = subWindow.upperLeft + gfx::Coord(subX, subY);
            drawPixel(pixCoord, pFrameBuf[pixCoord.x + (pixCoord.y * resolution.x)]);
        }
    }
}

void RenderBase::drawLine( const gfx::Coord&    p1,
                           const gfx::Coord&    p2,
                           const ColorRGB& colorRGB)
{
    if(p1.x == p2.x)
    {
        drawVLine(p1, abs(static_cast<int32_t>(p2.y) - static_cast<int32_t>(p1.y) + 1), colorRGB);
    }
    else if(p1.y == p2.y)
    {
        drawHLine(p1, abs(static_cast<int32_t>(p2.x) - static_cast<int32_t>(p1.x) + 1), colorRGB);
    }
    else
    {
        _drawLine(p1, p2, colorRGB);
    }

}
void RenderBase::drawHLine(const gfx::Coord&    p1,
                                    gfx::Pixel           width,
                                    const ColorRGB& colorRGB)
{
   for(auto x = p1.x; x <  p1.x + width; ++x)
    {
        drawPixel(gfx::Coord(x, p1.y), colorRGB);
    } 
}
void RenderBase::drawVLine(const gfx::Coord&    p1,
                                    gfx::Pixel           height,
                                    const ColorRGB& colorRGB)
{
    for(auto y = p1.y; y <  p1.y + height; ++y)
    {
        drawPixel(gfx::Coord(p1.x, y), colorRGB);
    }
}
void RenderBase::drawRectangle(const gfx::Rectangle& rect,
                                        const ColorRGB&  colorRGB,
                                        bool                           filled)
{
    if(filled)
    {
        for(auto y = rect.upperLeft.y; y <= rect.lowerRight.y; ++y)
        {
            drawHLine(gfx::Coord(rect.upperLeft.x, y), rect.width(), colorRGB);
        }
    }
    else
    {
        drawHLine(rect.upperLeft, rect.width(), colorRGB);
        drawHLine(gfx::Coord(rect.upperLeft.x, rect.lowerRight.y), rect.width(), colorRGB);
        drawVLine(rect.upperLeft, rect.height(), colorRGB);
        drawVLine(gfx::Coord(rect.lowerRight.x, rect.upperLeft.y), rect.height(), colorRGB);
    }   
}

void RenderBase::drawText( const gfx::Coord&    textMidLinePos,
                                    const ColorRGB& colorRGB,
                                    const std::string&            str )
{
    m_fontRenderer.drawText(textMidLinePos, colorRGB, str);
}

void RenderBase::setFont(const GfxFont& rFont, uint8_t scaleFactor)
{
    m_fontRenderer.setFont(rFont, scaleFactor);
}

void RenderBase::getRenderedTextSize(const std::string&      txt,
                                              const GfxFont*          pFont,
                                              gfx::Size2D&   size,
                                              gfx::Offset2D& offset)
{
    m_fontRenderer.getRenderedTextSize(txt, pFont, size, offset);
}

void RenderBase::_drawLine(const gfx::Coord&    p1,
                                    const gfx::Coord&    p2,
                                    const ColorRGB& colorRGB)
{
    gfx::Pixel x0 = p1.x;
    gfx::Pixel y0 = p1.y;
    gfx::Pixel x1 = p2.x;
    gfx::Pixel y1 = p2.y;
    
    bool steep = abs(static_cast<int32_t>(y1) - static_cast<int32_t>(y0)) > abs(static_cast<int32_t>(x1) - static_cast<int32_t>(x0));
    if(steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if(x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    gfx::Pixel dx = x1 - x0;
    gfx::Pixel dy = abs(static_cast<int32_t>(y1) - static_cast<int32_t>(y0));

    int32_t err = dx / 2;
    int32_t ystep;

    if(y0 < y1)
    {
        ystep = 1;
    }
    else
    {
        ystep = -1;
    }

    for(; x0 <= x1; x0++)
    {
        gfx::Coord pos;
        if(steep)
        {
            pos.x = y0;
            pos.y = x0;
        }
        else
        {
            pos.x = x0;
            pos.y = y0;
        }
        drawPixel(pos, colorRGB);
        err -= dy;
        if(err < 0)
        {
            y0 += ystep;
            err += dx;
        }
    } 
}

