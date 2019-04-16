#ifndef FP_RENDER_IF_H
#define FP_RENDER_IF_H

#include "FpIRender.h"
#include "FpVector2D.h"

namespace fp
{

class RenderIf : public IRender
{
public:
    virtual bool setFrameBufRendering(bool on) = 0;
};

} // namespace fp
#endif