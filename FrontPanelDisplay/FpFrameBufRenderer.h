#ifndef DISPLAY_FRAMEBUF_RENDERER
#define DISPLAY_FRAMEBUF_RENDERER

#include "FpRenderBase.h"
#include "FpDisplayFrameBuffer.h"

namespace fp
{

class FrameBufRenderer : public RenderBase
{
public:
    FrameBufRenderer(DisplayFrameBuffer& rFrameBuffer);
    virtual void drawPixel(const gfx::Coord& pixPos,
                           const ColorRGB& colorRGB);
private:
    DisplayFrameBuffer& m_rFrameBuffer;
};

} // namespace fp
#endif