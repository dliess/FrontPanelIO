#include "FpDoubleBufAnalyzer.h"
#include "FpColorRGB.h"
#include <limits>
#include <algorithm>

using namespace fp;

const gfx::Pixel DoubleBufAnalyzer::MAX = std::numeric_limits<gfx::Pixel>::max();

DoubleBufAnalyzer::DoubleBufAnalyzer(const DisplayFrameBuffer& rActualFrameBuffer,
                                     const DisplayFrameBuffer& rPrevFrameBuffer) :
    m_rActualFrameBuffer(rActualFrameBuffer),
    m_rPrevFrameBuffer(rPrevFrameBuffer),
    m_diffArea(gfx::Coord(MAX, MAX),gfx::Coord(0, 0)),
    m_numDiffPixels(0)
    {}

void DoubleBufAnalyzer::analyze()
{
    m_diffArea = {gfx::Coord(MAX, MAX),gfx::Coord(0, 0)},
    m_numDiffPixels = 0;

    const auto resolution = m_rActualFrameBuffer.resolution();
    for(gfx::Pixel y = 0; y < resolution.y; ++y)
    {
        for(gfx::Pixel x = 0; x < resolution.x; ++x)
        {
            if(m_rActualFrameBuffer.at(x, y) != m_rPrevFrameBuffer.at(x, y))
            {
                ++m_numDiffPixels;
                m_diffArea.upperLeft.x = std::min(x, m_diffArea.upperLeft.x);
                m_diffArea.lowerRight.x = std::max(x, m_diffArea.lowerRight.x); 
                if(MAX == m_diffArea.upperLeft.y)
                {
                    m_diffArea.upperLeft.y = y;
                }
                m_diffArea.lowerRight.y = y;
            }
        }
    }
}

uint32_t DoubleBufAnalyzer::getNumDiffPixels() const
{
    return m_numDiffPixels;
}

const gfx::Rectangle &DoubleBufAnalyzer::diffArea() const
{
    return m_diffArea;
}
