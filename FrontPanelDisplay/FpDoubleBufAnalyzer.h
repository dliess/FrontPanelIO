#ifndef FP_DOUBLE_BUF_ANALYZER_H
#define FP_DOUBLE_BUF_ANALYZER_H

#include "FpGfxTypes.h"
#include "FpDisplayFrameBuffer.h"

namespace fp
{

class DoubleBufAnalyzer
{
public:
    DoubleBufAnalyzer(const DisplayFrameBuffer& rActualFrameBuffer,
                      const DisplayFrameBuffer& rPrevFrameBuffer);
    void analyze();
    uint32_t getNumDiffPixels() const;
    const gfx::Rectangle &diffArea() const;
private:
    const DisplayFrameBuffer& m_rActualFrameBuffer;
    const DisplayFrameBuffer& m_rPrevFrameBuffer;
    gfx::Rectangle        m_diffArea;
    uint32_t                  m_numDiffPixels;
    static const gfx::Pixel MAX;
};

} // namespace fp
#endif