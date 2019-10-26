#ifndef FP_LED_SCENE_HANDLER_H
#define FP_LED_SCENE_HANDLER_H

#include "FpLed.h"
#include "FpTopologyContainer.h"
#include "FpCallbackStack.h"

namespace fp
{

template<typename Derived, int StackDepth = 3>
class LedSceneHandler
{
public:
    void reserveLed(Led::ILedScene& ledScene, const Widget& w, const Led::ColorRGB& colorRGB);
    void releaseLed(Led::ILedScene& ledScene, const Widget& w);
    void setLed(Led::ILedScene& ledScene, const Widget& w, const Led::ColorRGB& colorRGB);
private:
    struct LedSceneData 
    {
        Led::ILedScene* pLedScene;
        Led::ColorRGB   color;
        LedSceneData(const Led::ILedScene &ledScene) : pLedScene(&ledScene) {}
        LedSceneData(const Led::ILedScene &ledScene, const Led::ColorRGB& colorRGB) : pLedScene(&ledScene), color(colorRGB) {}
        bool operator==(const LedSceneData& rhs) const noexcept{ return pLedScene == rhs.pLedScene;}
        bool operator!=(const LedSceneData& rhs) const noexcept{ return !operator==(rhs);}
    };
    using LedSceneContainer = TopologyContainer<CallbackStack<LedSceneData, StackDepth>, typename Push2Topology::Led>;
    LedSceneContainer m_ledSceneContainer;
    const Derived& derived() const noexcept;
    Derived& derived() noexcept;
};

} //namespace fp

template<typename Derived, int StackDepth>
void fp::LedSceneHandler<Derived, StackDepth>::reserveLed(fp::Led::ILedScene& ledScene, const fp::Widget& w, const Led::ColorRGB& colorRGB)
{
    auto stack = m_ledSceneContainer.get(w);
    if(stack)
    {
        auto actual = stack->getActual();
        if(actual)
        {
            if(actual->pLedScene == &ledScene)
            {
                return;
            }
            else
            {
                actual->pLedScene->onGotHidden(w);
            }
        }
        stack->pushBack({&ledScene, colorRGB});
        derived().setLed(w, colorRGB);
    }
}

template<typename Derived, int StackDepth>
void fp::LedSceneHandler<Derived, StackDepth>::releaseLed(fp::Led::ILedScene& ledScene, const fp::Widget& w)
{
    auto stack = m_ledSceneContainer.get(w);
    if(stack)
    {
        stack->remove(LedSceneData(ledScene));
        auto actual = stack->getActual();
        if(actual && actual->pLedScene == &ledScene)
        {
            auto newActual = stack->getActual();
            if(newActual)
            {
                newActual->pLedScene->onGotRevealed(w);
                derived().setLed(w, newActual->color);
            }
        }
    }
}

template<typename Derived, int StackDepth>
void fp::LedSceneHandler<Derived, StackDepth>::setLed(fp::Led::ILedScene& ledScene, const fp::Widget& w, const fp::Led::ColorRGB& colorRGB)
{
    auto stack = m_ledSceneContainer.get(w);
    if(stack)
    {
        auto actual = stack->getActual();
        if(actual && actual->pLedScene == &ledScene)
        {
            stack->actual()->color = colorRGB;
            derived().setLed(w, colorRGB);
        }
    }
}

template<typename Derived, int StackDepth>
const Derived& fp::LedSceneHandler<Derived, StackDepth>::derived() const noexcept
{
    return *(static_cast<Derived*>(this));
}

template<typename Derived, int StackDepth>
Derived& fp::LedSceneHandler<Derived, StackDepth>::derived() noexcept
{
    return *(static_cast<Derived*>(this));
}


#endif