#ifndef FP_BUTTON5D_H
#define FP_BUTTON5D_H

#include <cstdint>
#include "FpVector2D.h"
#include <FpValue.h>

namespace fp
{
struct Widget;
}

namespace fp
{

class Button5d
{
public:
    enum PressState
    {
        Released = 0,
        Pressed
    };
    struct StateData
    {
        PressState pressState;
        uint32_t   velocity;
    };
    struct PositionEventData
    {
      uint32_t pressure;
      Vector2d<uint32_t> surfacePosition;
    };
    class CallbackIf
    {
    public:
        virtual void onPressStateChange(const StateData& data, const Widget& w) = 0;
        virtual void onPositionEvents(const PositionEventData& data, const Widget& w) = 0;
    };
    struct ValueHolder
    {
        void fireCallbacksAndReset(CallbackIf& cbIf, const Widget& w)
        {
            if(pressState.hasChanged())
            {
                cbIf.onPressStateChange({pressState.value(), velocity}, w);
                pressState.resetState();
            }
            if(pressure.hasChanged())
            {
                cbIf.onPositionEvents({pressure.value(), surfacePosition.value()}, w);
                pressure.resetState();
            }
            if(surfacePosition.hasChanged())
            {
                cbIf.onPositionEvents({pressure.value(), surfacePosition.value()}, w);
                surfacePosition.resetState();
            }
        }
        Value<PressState>           pressState;
        uint32_t                           velocity;
        Value<uint32_t>             pressure;
        Value< Vector2d<uint32_t> > surfacePosition;
    };
    class IProvider
    {
    public:
        virtual void registerCB(Button5d::CallbackIf& cb, const Widget& w) = 0;
    };
};


 
} // namespace fp
#endif