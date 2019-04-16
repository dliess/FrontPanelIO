#ifndef FP_DOUBLE_BUF_HANDLER_H
#define FP_DOUBLE_BUF_HANDLER_H

#include "FpFrameBufRenderer.h"
#include "FpDisplayFrameBuffer.h"

namespace fp
{

template<class DirectRenderIf>
class DoubleBufHandler : public FrameBufRenderer
{
public:
    DoubleBufHandler(DirectRenderIf& rDirectRenderIf);
    void flushFrameBuffer();
   // DisplayFrameBuffer& actualFrameBuf();
private:
    DirectRenderIf&    m_rDirectRenderIf;
    DisplayFrameBuffer m_actualFrameBuf;
    DisplayFrameBuffer m_prevFrameBuf;

    void streamDiffArea(const gfx::Rectangle& diffRectangle);
    void drawDiffPixelsOneByOne(const gfx::Rectangle& diffRectangle);
    gfx::Resolution getResolution() const override;
};

} // namespace fp
#include "FpDoubleBufHandler.tcc"
#endif