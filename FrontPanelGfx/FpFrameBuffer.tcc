#include <string.h> // memset()

using namespace fp;

template<class Color>
FrameBuffer<Color>::FrameBuffer(const gfx::Resolution& resolution) :
    m_resolution(resolution),
    m_dirty(false)
{
    const auto numPix = m_resolution.x * m_resolution.y;
    m_pFrameBuf = new Color[numPix];
    clear();
}

template<class Color>
FrameBuffer<Color>::~FrameBuffer()
{
    delete m_pFrameBuf;
}

template<class Color>
Color& FrameBuffer<Color>::at(gfx::Pixel x, gfx::Pixel y)
{
    if(x >= m_resolution.x || y >= m_resolution.y)
    {
        //TODO: Log internal error
        return getDummyElement();
    }
    m_dirty = true;
    return m_pFrameBuf[x + (m_resolution.x * y)];
}

template<class Color>
const Color& FrameBuffer<Color>::at(gfx::Pixel x, gfx::Pixel y) const
{
    if(x >= m_resolution.x || y >= m_resolution.y)
    {
        //TODO: Log internal error
        return getDummyElement();
    }
    return m_pFrameBuf[x + (m_resolution.x * y)];
}

template<class Color>
Color& FrameBuffer<Color>::at(const gfx::Coord& pixPos)
{
    return at(pixPos.x, pixPos.y);
}

template<class Color>
const Color& FrameBuffer<Color>::at(const gfx::Coord& pixPos) const
{
    return at(pixPos.x, pixPos.y);
}

template<class Color>
void FrameBuffer<Color>::switchBuffers(FrameBuffer& other)
{
    Color* tmp = m_pFrameBuf;
    m_pFrameBuf = other.m_pFrameBuf;
    other.m_pFrameBuf = tmp;
}

template<class Color>
const gfx::Resolution& FrameBuffer<Color>::resolution() const
{
    return m_resolution;
}


template<class Color>
void FrameBuffer<Color>::clear()
{
    memset(m_pFrameBuf, 0, m_resolution.x * m_resolution.y * sizeof(Color));
    m_dirty = false;
}


template<class Color>
bool FrameBuffer<Color>::isDirty() const
{
    return m_dirty;
}

template<class Color>
const Color* FrameBuffer<Color>::getBuffer() const
{
    return m_pFrameBuf;
}

template<class Color>
const uint8_t *FrameBuffer<Color>::getRawBuffer() const
{
    return reinterpret_cast<uint8_t*>(m_pFrameBuf);
}

template<class Color>
unsigned int FrameBuffer<Color>::size() const
{
    return m_resolution.x * m_resolution.y * sizeof(Color);
}

template<class Color>
Color &FrameBuffer<Color>::getDummyElement()
{
    static Color dummyElement;
    return dummyElement;
}