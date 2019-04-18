#ifndef FP_TOUCH_SURFACE_H
#define FP_TOUCH_SURFACE_H

#include "FpVector2D.h"
#include "FpValue.h"
#include <cstdint>

namespace fp
{
struct Widget;
}

namespace fp
{

class TouchSurface
{
public:
    enum TouchState
    {
        Released = 0,
        Touched = 1
    };
    struct PressData
    {
        Vector2d<int32_t> pos;
        uint32_t          pressure;
    };
    class CallbackIf
    {
    public:
        virtual void onTouchStateChanged(TouchState touchState, const Widget& w) = 0;
        virtual void onPositionEvents(const PressData& data, const Widget& w) = 0;
    };
    struct ValueHolder
    {
        void fireCallbacksAndReset(CallbackIf& cbIf, const Widget& w)
        {
            if(touchState.hasChanged())
            {
                cbIf.onTouchStateChanged(touchState.value(), w);
                touchState.resetState();
            }
            if(pos.hasChanged())
            {
                cbIf.onPositionEvents({pos.value(), pressure.value()}, w);
                pos.resetState();
            }
            if(pressure.hasChanged())
            {
                cbIf.onPositionEvents({pos.value(), pressure.value()}, w);
                pressure.resetState();
            }
        }
        Value<TouchState>        touchState;
        Value<Vector2d<int32_t>> pos;
        Value<uint32_t>          pressure;
    };
    class IProvider
    {
    public:
        virtual void registerCB(typename TouchSurface::CallbackIf& cb, const Widget& w) = 0;
    };
};

 
} // namespace fp
#endif