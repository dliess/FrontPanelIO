#ifndef FP_RENDER_CB_IF
#define FP_RENDER_CB_IF

class RenderIf;

namespace fp
{

class RenderCbIf
{
public:
    virtual void revealed(RenderIf& r) = 0; 
    virtual void renderDisplays(RenderIf& r) = 0; 
};

} // namespace fp
#endif