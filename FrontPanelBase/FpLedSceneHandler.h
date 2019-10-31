#ifndef FP_LED_SCENE_HANDLER_H
#define FP_LED_SCENE_HANDLER_H

#include "FpLed.h"
#include "FpTopologyContainer.h"
#include "FpCallbackStack.h"

namespace fp
{

template<typename Derived, typename LedTopology, int StackDepth = 3>
class LedSceneHandler
{
public:
    void reserveLed(Led::ILedScene* pLedScene, const Widget& w, const Led::ColorRGB& colorRGB);
    void releaseLed(Led::ILedScene* pLedScene, const Widget& w);
    void setLedOfScene(Led::ILedScene* pLedScene, const Widget& w, const Led::ColorRGB& colorRGB);
private:
    struct LedSceneData 
    {
        Led::ILedScene* pLedScene;
        Led::ColorRGB   color;
        LedSceneData(Led::ILedScene *pLedScene) : pLedScene(pLedScene) {}
        LedSceneData(Led::ILedScene *pLedScene, const Led::ColorRGB& colorRGB) : pLedScene(pLedScene), color(colorRGB) {}
        bool operator==(const LedSceneData& rhs) const noexcept{ return pLedScene == rhs.pLedScene;}
        bool operator!=(const LedSceneData& rhs) const noexcept{ return !operator==(rhs);}
    };
    using LedSceneContainer = TopologyContainer<CallbackStack<LedSceneData, StackDepth>, LedTopology>;
    LedSceneContainer m_ledSceneContainer;
    const Derived& derived() const noexcept;
    Derived& derived() noexcept;
};

} //namespace fp

template<typename Derived, typename LedTopology, int StackDepth>
void fp::LedSceneHandler<Derived, LedTopology, StackDepth>::reserveLed(fp::Led::ILedScene* pLedScene,
                                                                       const fp::Widget& w,
                                                                       const Led::ColorRGB& colorRGB)
{
    forWidget<LedTopology>(w, [this, &pLedScene, &colorRGB](const fp::Widget _w){
        auto stack = m_ledSceneContainer.get(_w);
        if(stack)
        {
            auto actual = stack->getActual();
            if(actual)
            {
                if(actual->pLedScene == pLedScene)
                {
                    return;
                }
                else
                {
                    actual->pLedScene->onGotHidden(_w);
                }
            }
            stack->pushBack(LedSceneData(pLedScene, colorRGB));
            derived().setLed(_w, colorRGB);
        }
    });
}

template<typename Derived, typename LedTopology, int StackDepth>
void fp::LedSceneHandler<Derived, LedTopology, StackDepth>::releaseLed(fp::Led::ILedScene* pLedScene,
                                                                       const fp::Widget& w)
{
    forWidget<LedTopology>(w, [this, &pLedScene](const fp::Widget _w){
        auto stack = m_ledSceneContainer.get(_w);
        if(stack)
        {
            const bool wasActual = (stack->getActual() == pLedScene);
            stack->remove(LedSceneData(pLedScene));
            if(wasActual)
            {
                auto newActual = stack->getActual();
                if(newActual)
                {
                    newActual->pLedScene->onGotRevealed(_w);
                    derived().setLed(_w, newActual->color);
                }
            }
        }
    });
}

template<typename Derived, typename LedTopology, int StackDepth>
void fp::LedSceneHandler<Derived, LedTopology, StackDepth>::setLedOfScene(fp::Led::ILedScene* pLedScene,
                                                                          const fp::Widget& w,
                                                                          const fp::Led::ColorRGB& colorRGB)
{
    forWidget<LedTopology>(w, [this, &pLedScene, &colorRGB](const fp::Widget _w){
        auto stack = m_ledSceneContainer.get(_w);
        if(stack)
        {
            stack->forEach([&pLedScene, &colorRGB](LedSceneData& ledSceneData){
                if(ledSceneData.pLedScene == pLedScene)
                {
                    ledSceneData.color = colorRGB;
                }
            });
            auto actual = stack->getActual();
            if(actual && actual->pLedScene == pLedScene)
            {
                derived().setLed(_w, colorRGB);
            }
        }
    });
}

template<typename Derived, typename LedTopology, int StackDepth>
const Derived& fp::LedSceneHandler<Derived, LedTopology, StackDepth>::derived() const noexcept
{
    return *(static_cast<Derived*>(this));
}

template<typename Derived, typename LedTopology, int StackDepth>
Derived& fp::LedSceneHandler<Derived, LedTopology, StackDepth>::derived() noexcept
{
    return *(static_cast<Derived*>(this));
}


#endif