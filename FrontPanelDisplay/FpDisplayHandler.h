#ifndef FP_DISPLAY_HANDLER_H
#define FP_DISPLAY_HANDLER_H

#include "FpRenderCbIf.h"
#include "FpCallbackStack.h"
#include "FpWidget.h"
#include "FpRenderCbIf.h"

namespace fp
{

template<class RenderMediumProvider>
class DisplayHandler
{
public:
    DisplayHandler(RenderMediumProvider& rRenderMediumProvider);
    DisplayHandler(DisplayHandler&& rhs);
    void registerRenderCbIf(RenderCbIf& cbIf, const Widget& w);
    void unregisterRenderCbIf(RenderCbIf& cbIf, const Widget& w);
    void renderDisplay(const Widget& w);
    void renderDisplays();

private:
    RenderMediumProvider& m_rRenderMediumProvider;
    using DisplayCbStack = CallbackStack<RenderCbIf*, 3>;
    using DisplayTopology = typename RenderMediumProvider::DisplayTopology;
    TopologyContainer<DisplayCbStack, DisplayTopology> m_displayCbContainer;
};

template<class RenderMediumProvider>
DisplayHandler<RenderMediumProvider> displayHandler(RenderMediumProvider& rRenderMediumProvider)
{
    DisplayHandler<RenderMediumProvider> displayHandler(rRenderMediumProvider);
    return displayHandler;
}

} // namespace fp
#include "FpDisplayHandler.tcc"
#endif