#ifndef FP_FONT_H
#define FP_FONT_H

#include <cstdint>
#include "FpSize2D.h"
#include "FpGfxTypes.h"

namespace fp
{

typedef struct {
	uint16_t bitmapOffset;
	uint8_t  width;
    uint8_t  height;
	uint8_t  xAdvance;
	int8_t   xOffset;
    int8_t   yOffset;
} GfxGlyph;

class GfxFont
{
public:
    enum FontType
    {
        MONOSPACED   = 0,
        PROPORTIONAL = 1
    };
    GfxFont(FontType  type,
	        uint8_t  *pBitmap,
            GfxGlyph *pGlyph,
            uint8_t   first,
            uint8_t   last,
            uint8_t   yAdvance) :
    m_type(type),
    m_pBitmap(pBitmap),
    m_pGlyph(pGlyph),
    m_first(first),
    m_yAdvance(yAdvance)
    {}
    FontType getType() const
    {
        return m_type;
    }
    
    gfx::Size2D getSize(unsigned char c = 0) const
    {
        switch(m_type)
        {
            case MONOSPACED:
                return {m_pGlyph[0].width, m_pGlyph[0].height};
            case PROPORTIONAL:
            default:
            {
                c -= m_first;
                return {m_pGlyph[c].width, m_pGlyph[c].height};
            }
        }
    }

    gfx::Offset2D getAdvance(unsigned char c = 0) const
    {
        switch(m_type)
        {
            case MONOSPACED:
                return {m_pGlyph[0].xAdvance, m_yAdvance};
            case PROPORTIONAL:
            default:
            {
                c -= m_first;
                return {m_pGlyph[c].xAdvance, m_yAdvance};
            }
        }
    }


    uint8_t* getPixMapStart(unsigned char c) const
    {
        switch(m_type)
        {
            case MONOSPACED:
                return &m_pBitmap[c * m_pGlyph[0].width];
            case PROPORTIONAL:
            default:
            {
                c -= m_first;
                return &m_pBitmap[m_pGlyph[c].bitmapOffset];
            }
        }
    }

    gfx::Offset2D getOffset(unsigned char c = 0) const
    {
        switch(m_type)
        {
            case MONOSPACED:
                return {m_pGlyph[0].xOffset, m_pGlyph[0].yOffset};
            case PROPORTIONAL:
            default:
            {
                c -= m_first;
                return {m_pGlyph[c].xOffset, m_pGlyph[c].yOffset};
            }
        }
    }


private:
    FontType  m_type;
	uint8_t  *m_pBitmap;
	GfxGlyph *m_pGlyph;
	uint8_t   m_first;
	uint8_t   m_yAdvance;
};

} // namespace fp
#endif // FP_FONT_H
