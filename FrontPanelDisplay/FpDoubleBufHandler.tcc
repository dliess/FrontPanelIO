#include "FpDoubleBufHandler.h"
#include "FpDoubleBufAnalyzer.h"

using namespace fp;

template<class DirectRenderIf>
DoubleBufHandler<DirectRenderIf>::DoubleBufHandler(DirectRenderIf& rDirectRenderIf) :
    FrameBufRenderer(m_actualFrameBuf),
    m_rDirectRenderIf(rDirectRenderIf),            
    m_actualFrameBuf(rDirectRenderIf.getResolution()),
    m_prevFrameBuf(rDirectRenderIf.getResolution())
{
}

template<class DirectRenderIf>
void DoubleBufHandler<DirectRenderIf>::flushFrameBuffer()
{
    if(!m_actualFrameBuf.isDirty())
    {
        return;
    }
    DoubleBufAnalyzer frameBufAnalyzer(m_actualFrameBuf,
                                      m_prevFrameBuf);
    frameBufAnalyzer.analyze();
    const auto numDiffPixels = frameBufAnalyzer.getNumDiffPixels();
    if(numDiffPixels > 0)
    {
        const auto ratio = numDiffPixels * 100 / frameBufAnalyzer.diffArea().getNumPixels();
        if(ratio > m_rDirectRenderIf.getDiscretePixelOverFrameStreamPercentage())
        {
            streamDiffArea(frameBufAnalyzer.diffArea());
        }
        else
        {
            drawDiffPixelsOneByOne(frameBufAnalyzer.diffArea());
        }
        m_actualFrameBuf.switchBuffers(m_prevFrameBuf);
    }
    m_actualFrameBuf.clear();
}

/*
template<class DirectRenderIf>
DisplayFrameBuffer& DoubleBufHandler<DirectRenderIf>::actualFrameBuf()
{
    return m_actualFrameBuf;
}
*/

template<class DirectRenderIf>
void DoubleBufHandler<DirectRenderIf>::streamDiffArea(const gfx::Rectangle& diffRectangle)
{
    m_rDirectRenderIf.streamFromFramebuf(diffRectangle,
                                              m_actualFrameBuf.resolution(),
                                              m_actualFrameBuf.getBuffer());
}

template<class DirectRenderIf>
void DoubleBufHandler<DirectRenderIf>::drawDiffPixelsOneByOne(const gfx::Rectangle& diffRectangle)
{
    for(gfx::Pixel y = diffRectangle.upperLeft.y; y <= diffRectangle.lowerRight.y; ++y)
    {
        for(gfx::Pixel x = diffRectangle.upperLeft.x; x <= diffRectangle.lowerRight.x; ++x)
        {
            if(m_actualFrameBuf.at(x, y) != m_prevFrameBuf.at(x, y))
            {
                m_rDirectRenderIf.drawPixel(gfx::Coord(x,y), m_actualFrameBuf.at(x, y));
            }
        }
    }
}

template<class DirectRenderIf>
gfx::Resolution DoubleBufHandler<DirectRenderIf>::getResolution() const
{
    return m_actualFrameBuf.resolution();
}

