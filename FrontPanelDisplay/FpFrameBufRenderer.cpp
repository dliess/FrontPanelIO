#include "FpFrameBufRenderer.h"

using namespace fp;

FrameBufRenderer::FrameBufRenderer(DisplayFrameBuffer& rFrameBuffer) :
    m_rFrameBuffer(rFrameBuffer)
    {}

void FrameBufRenderer::drawPixel(const gfx::Coord&    pixPos,
                                const ColorRGB& colorRGB)
{
    m_rFrameBuffer.at(pixPos) = colorRGB;
}