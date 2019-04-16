#ifndef FP_INTERFACE_RENDER_MEDIUM_H
#define FP_INTERFACE_RENDER_MEDIUM_H

#include "FpRenderIf.h"

namespace fp
{

class IRenderMedium : public RenderIf
{
public:
    virtual void flushFrameBuffer() = 0;
};

} // namespace fp
#endif