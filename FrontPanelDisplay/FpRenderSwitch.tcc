#include "FpRenderSwitch.h"

using namespace fp;

template <class DirectRenderInterface, class FrameBufInterface>
RenderSwitch<DirectRenderInterface, FrameBufInterface>::RenderSwitch(DirectRenderInterface& rDirectRenderInterface,
                                                                     FrameBufInterface&     rFrameBufInterface) :
    m_rDirectRenderInterface(rDirectRenderInterface),
    m_rFrameBufInterface(rFrameBufInterface),
    m_frameBufRendering(false)
{
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::flushFrameBuffer()
{
    m_rFrameBufInterface.flushFrameBuffer();
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::drawPixel( const gfx::Coord&    pixPos,
                                const ColorRGB& colorRGB)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.drawPixel(pixPos, colorRGB);
    }
    else
    {
        m_rDirectRenderInterface.drawPixel(pixPos, colorRGB);
    }
}        

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::streamToSubWindow(const gfx::Rectangle& subWindow,
                                       const ColorRGB*  pPixelStream)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.streamToSubWindow(subWindow, pPixelStream);
    }
    else
    {
        m_rDirectRenderInterface.streamToSubWindow(subWindow, pPixelStream);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::streamFromFramebuf(const gfx::Rectangle& subWindow,
                                        const gfx::Resolution& resolution,
                                        const ColorRGB*  pFrameBuf)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.streamFromFramebuf(subWindow, resolution, pFrameBuf);
    }
    else
    {
        m_rDirectRenderInterface.streamFromFramebuf(subWindow, resolution, pFrameBuf);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::drawLine(const gfx::Coord&    p1,
                              const gfx::Coord&    p2,
                              const ColorRGB& colorRGB)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.drawLine(p1, p2, colorRGB);
    }
    else
    {
        m_rDirectRenderInterface.drawLine(p1, p2, colorRGB);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::drawHLine(const gfx::Coord&    p1,
                                    gfx::Pixel           width,
                                    const ColorRGB& colorRGB)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.drawHLine(p1, width, colorRGB);
    }
    else
    {
        m_rDirectRenderInterface.drawHLine(p1, width, colorRGB);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::drawVLine(const gfx::Coord&  p1,
                                    gfx::Pixel            height,
                                    const ColorRGB&  colorRGB)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.drawVLine(p1, height, colorRGB);
    }
    else
    {
        m_rDirectRenderInterface.drawVLine(p1, height, colorRGB);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::drawRectangle(const gfx::Rectangle& rect,
                                   const ColorRGB&  colorRGB,
                                   bool                           filled)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.drawRectangle(rect, colorRGB, filled);
    }
    else
    {
        m_rDirectRenderInterface.drawRectangle(rect, colorRGB, filled);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::drawText(const gfx::Coord&    textMidLinePos,
                              const ColorRGB& colorRGB,
                              const std::string&            str)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.drawText(textMidLinePos, colorRGB, str);
    }
    else
    {
        m_rDirectRenderInterface.drawText(textMidLinePos, colorRGB, str);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::setFont(const GfxFont& rFont, uint8_t scaleFactor)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.setFont(rFont, scaleFactor);
    }
    else
    {
        m_rDirectRenderInterface.setFont(rFont, scaleFactor);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
void RenderSwitch<DirectRenderInterface, FrameBufInterface>::getRenderedTextSize(const std::string&      txt,
                                         const GfxFont*          pFont,
                                         gfx::Size2D&   size,
                                         gfx::Offset2D& offset)
{
    if(m_frameBufRendering)
    {
        m_rFrameBufInterface.getRenderedTextSize(txt, pFont, size, offset);
    }
    else
    {
        m_rDirectRenderInterface.getRenderedTextSize(txt, pFont, size, offset);
    }
}

template <class DirectRenderInterface, class FrameBufInterface>
bool RenderSwitch<DirectRenderInterface, FrameBufInterface>::setFrameBufRendering(bool on)
{
    m_frameBufRendering = on;
    return true;
}

template <class DirectRenderInterface, class FrameBufInterface>
gfx::Resolution RenderSwitch<DirectRenderInterface, FrameBufInterface>::getResolution() const
{
    return m_rDirectRenderInterface.getResolution();
}
