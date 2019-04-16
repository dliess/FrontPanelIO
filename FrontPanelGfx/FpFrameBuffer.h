#ifndef FP_FRAMEBUFFER_H
#define FP_FRAMEBUFFER_H

#include "FpGfxTypes.h"
#include <cstdint>

namespace fp
{

template<class Color>
class FrameBuffer
{
public:
    FrameBuffer(const gfx::Resolution& resolution);
    ~FrameBuffer();
    Color& at(gfx::Pixel x, gfx::Pixel y);
    const Color& at(gfx::Pixel x, gfx::Pixel y) const;
    Color& at(const gfx::Coord& pixPos);
    const Color& at(const gfx::Coord& pixPos) const;
    void switchBuffers(FrameBuffer<Color>& other);
    const gfx::Resolution& resolution() const;
    void clear();
    bool isDirty() const;
    const Color* getBuffer() const;
    const uint8_t *getRawBuffer() const;
    unsigned int size() const;
private:
    gfx::Resolution m_resolution;
    Color*          m_pFrameBuf;
    bool            m_dirty;
    static Color &getDummyElement();
};

} // namespace fp
#include "FpFrameBuffer.tcc"
#endif