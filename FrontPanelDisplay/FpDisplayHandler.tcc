#include "FpDisplayHandler.h"

using namespace fp;

template<class RenderMediumProvider>
DisplayHandler<RenderMediumProvider>::DisplayHandler(RenderMediumProvider& rRenderMediumProvider) :
    m_rRenderMediumProvider(rRenderMediumProvider)
{
}

#include <iostream>
template<class RenderMediumProvider>
DisplayHandler<RenderMediumProvider>::DisplayHandler(DisplayHandler&& rhs) :
    m_rRenderMediumProvider(rhs.m_rRenderMediumProvider),
    m_displayCbContainer(std::move(m_displayCbContainer))
{
    std::cout << "Move constructor called";
}


template<class RenderMediumProvider>
void DisplayHandler<RenderMediumProvider>::renderDisplay(const Widget& w)
{
    m_displayCbContainer.forWidget(w, [this](DisplayCbStack& cbStack, const Widget& w){
        auto pActual = cbStack.getActual();
        if(pActual)
        {
            auto pRenderMedium = m_rRenderMediumProvider.getRenderMedium(w);
            if(pRenderMedium)
            {
                pActual->renderDisplays(*pRenderMedium);
                pRenderMedium->flushFrameBuffer();
            }
        }
    });
}

template<class RenderMediumProvider>
void DisplayHandler<RenderMediumProvider>::renderDisplays()
{
    m_displayCbContainer.forEach([this](DisplayCbStack& cbStack, const Widget& w){
        auto pActual = cbStack.getActual();
        if(pActual)
        {
            auto pRenderMedium = m_rRenderMediumProvider.getRenderMedium(w);
            if(pRenderMedium)
            {
                pActual->renderDisplays(*pRenderMedium);
                pRenderMedium->flushFrameBuffer();
            }
        }
    });
}

template<class RenderMediumProvider>
void DisplayHandler<RenderMediumProvider>::registerRenderCbIf(RenderCbIf& cbIf, const Widget& w)
{
    m_displayCbContainer.forWidget(w, [this,&cbIf](DisplayCbStack& cbStack, const Widget& w){
        cbStack.pushBack(&cbIf);
        auto pRenderMedium = m_rRenderMediumProvider.getRenderMedium(w);
        if(pRenderMedium)
        {
            cbIf.revealed(*pRenderMedium);
        }
    });
}

template<class RenderMediumProvider>
void DisplayHandler<RenderMediumProvider>::unregisterRenderCbIf(RenderCbIf& cbIf, const Widget& w)
{
    m_displayCbContainer.forWidget(w, [this,&cbIf](DisplayCbStack& cbStack, const Widget& w)
    {
        cbStack.remove(&cbIf);
        auto pActual = cbStack.getActual();
        if(pActual)
        {
            auto pRenderMedium = m_rRenderMediumProvider.getRenderMedium(w);
            if(pRenderMedium)
            {
                pActual->revealed(*pRenderMedium);
            }
        }
    });
}