#ifndef FP_RENDER_SWITCH_H
#define FP_RENDER_SWITCH_H

#include "FpIRenderMedium.h"
#include <memory>

namespace fp
{

template <class DirectRenderInterface, class FrameBufInterface>
class RenderSwitch : public IRenderMedium
{
public:
    RenderSwitch(DirectRenderInterface& rDirectRenderInterface,
                 FrameBufInterface&     rFrameBufInterface);
    virtual void drawPixel( const gfx::Coord&    pixPos,
                            const ColorRGB& colorRGB) override;
    virtual void streamToSubWindow(const gfx::Rectangle& subWindow,
                                   const ColorRGB*  pPixelStream) override;
    virtual void streamFromFramebuf(const gfx::Rectangle& subWindow,
                                    const gfx::Resolution& resolution,
                                    const ColorRGB* pFrameBuf) override;
    virtual void drawLine(const gfx::Coord&    p1,
                          const gfx::Coord&    p2,
                          const ColorRGB&          colorRGB) override;
    virtual void drawHLine(const gfx::Coord&    p1,
                           gfx::Pixel           width,
                           const ColorRGB&          colorRGB) override;
    virtual void drawVLine(const gfx::Coord&    p1,
                           gfx::Pixel           height,
                           const ColorRGB& colorRGB) override;
    virtual void drawRectangle(const gfx::Rectangle& rect,
                               const ColorRGB&  colorRGB,
                               bool filled) override;
    virtual void drawText(const gfx::Coord& textMidLinePos,
                          const ColorRGB&       colorRGB,
                          const std::string&    str) override;
    virtual void setFont(const GfxFont& rFont, uint8_t scaleFactor) override;
    virtual void getRenderedTextSize(const std::string&      txt,
                                     const GfxFont*          pFont,
                                     gfx::Size2D&   size,
                                     gfx::Offset2D& offset) override;
    virtual bool setFrameBufRendering(bool on) override;

    virtual void flushFrameBuffer() override;
    virtual gfx::Resolution getResolution() const override;
private:
    DirectRenderInterface& m_rDirectRenderInterface;
    FrameBufInterface&     m_rFrameBufInterface;
    bool m_frameBufRendering;
};


template <class DirectRenderInterface>
class DirectRendererMedium : public IRenderMedium
{
public:
    DirectRendererMedium(DirectRenderInterface& rDirectRenderInterface) :
        m_rDirectRenderInterface(rDirectRenderInterface)
    { 
    }
    virtual void drawPixel( const gfx::Coord&    pixPos,
                            const ColorRGB& colorRGB) override
    {
        m_rDirectRenderInterface.drawPixel(pixPos, colorRGB);
    }
    virtual void streamToSubWindow(const gfx::Rectangle& subWindow,
                                   const ColorRGB*  pPixelStream) override
    {
        m_rDirectRenderInterface.streamToSubWindow(subWindow, pPixelStream);
    }
    virtual void streamFromFramebuf(const gfx::Rectangle& subWindow,
                                    const gfx::Resolution& resolution,
                                    const ColorRGB*  pFrameBuf) override
    {
        m_rDirectRenderInterface.streamFromFramebuf(subWindow, resolution, pFrameBuf);
    }
    virtual void drawLine(const gfx::Coord&    p1,
                          const gfx::Coord&    p2,
                          const ColorRGB&          colorRGB) override
    {
        m_rDirectRenderInterface.drawLine(p1, p2, colorRGB);
    }
    virtual void drawHLine(const gfx::Coord&    p1,
                           gfx::Pixel           width,
                           const ColorRGB&          colorRGB) override
    {
        m_rDirectRenderInterface.drawHLine(p1, width, colorRGB);
    }
    virtual void drawVLine(const gfx::Coord&    p1,
                           gfx::Pixel           height,
                           const ColorRGB& colorRGB) override
    {
        m_rDirectRenderInterface.drawVLine(p1, height, colorRGB);
    }
    virtual void drawRectangle(const gfx::Rectangle& rect,
                               const ColorRGB&  colorRGB,
                               bool filled) override
    {
        m_rDirectRenderInterface.drawRectangle(rect, colorRGB, filled);
    }
    virtual void drawText(const gfx::Coord& textMidLinePos,
                          const ColorRGB&       colorRGB,
                          const std::string&    str) override
    {
        m_rDirectRenderInterface.drawText(textMidLinePos, colorRGB, str);
    }
    virtual void setFont(const GfxFont& rFont, uint8_t scaleFactor) override
    {
        m_rDirectRenderInterface.setFont(rFont, scaleFactor);
    }
    virtual void getRenderedTextSize(const std::string&      txt,
                                     const GfxFont*          pFont,
                                     gfx::Size2D&   size,
                                     gfx::Offset2D& offset) override
    {
        m_rDirectRenderInterface.getRenderedTextSize(txt, pFont, size, offset);
    }
    virtual bool setFrameBufRendering(bool on) override
    {
        return !on;
    }
    virtual void flushFrameBuffer() override
    {
        // do nothing, direct rendering won't flush
    }
    virtual gfx::Resolution getResolution() const override
    {
        return m_rDirectRenderInterface.getResolution();
    }

private:
    DirectRenderInterface& m_rDirectRenderInterface;
};

template <class FrameBufInterface>
class FrameBufRendererMedium : public IRenderMedium
{
public:
    FrameBufRendererMedium(FrameBufInterface& rFrameBufInterface) :
        m_rFrameBufInterface(rFrameBufInterface)
    { 
    }
    virtual void drawPixel( const gfx::Coord&    pixPos,
                            const ColorRGB& colorRGB) override
    {
        m_rFrameBufInterface.drawPixel(pixPos, colorRGB);
    }
    virtual void streamToSubWindow(const gfx::Rectangle& subWindow,
                                   const ColorRGB*  pPixelStream) override
    {
        m_rFrameBufInterface.streamToSubWindow(subWindow, pPixelStream);
    }
    virtual void streamFromFramebuf(const gfx::Rectangle& subWindow,
                                    const gfx::Resolution& resolution,
                                    const ColorRGB*  pFrameBuf) override
    {
        m_rFrameBufInterface.streamFromFramebuf(subWindow, resolution, pFrameBuf);
    }
    virtual void drawLine(const gfx::Coord&    p1,
                          const gfx::Coord&    p2,
                          const ColorRGB&          colorRGB) override
    {
        m_rFrameBufInterface.drawLine(p1, p2, colorRGB);
    }
    virtual void drawHLine(const gfx::Coord&    p1,
                           gfx::Pixel           width,
                           const ColorRGB&          colorRGB) override
    {
        m_rFrameBufInterface.drawHLine(p1, width, colorRGB);
    }
    virtual void drawVLine(const gfx::Coord&    p1,
                           gfx::Pixel           height,
                           const ColorRGB& colorRGB) override
    {
        m_rFrameBufInterface.drawVLine(p1, height, colorRGB);
    }
    virtual void drawRectangle(const gfx::Rectangle& rect,
                               const ColorRGB&  colorRGB,
                               bool filled) override
    {
        m_rFrameBufInterface.drawRectangle(rect, colorRGB, filled);
    }
    virtual void drawText(const gfx::Coord& textMidLinePos,
                          const ColorRGB&       colorRGB,
                          const std::string&    str) override
    {
        m_rFrameBufInterface.drawText(textMidLinePos, colorRGB, str);
    }
    virtual void setFont(const GfxFont& rFont, uint8_t scaleFactor) override
    {
        m_rFrameBufInterface.setFont(rFont, scaleFactor);
    }
    virtual void getRenderedTextSize(const std::string&      txt,
                                     const GfxFont*          pFont,
                                     gfx::Size2D&   size,
                                     gfx::Offset2D& offset) override
    {
        m_rFrameBufInterface.getRenderedTextSize(txt, pFont, size, offset);
    }
    virtual bool setFrameBufRendering(bool on) override
    {
        return on;
    }
    virtual void flushFrameBuffer() override
    {
        m_rFrameBufInterface.flushFrameBuffer();
    }
    virtual gfx::Resolution getResolution() const override
    {
        return m_rFrameBufInterface.getResolution();
    }
private:
    FrameBufInterface& m_rFrameBufInterface;
};


} // namespace fp
#include "FpRenderSwitch.tcc"
#endif