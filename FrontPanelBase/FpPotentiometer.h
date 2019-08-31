#ifndef FP_POTENTIOMETER_H
#define FP_POTENTIOMETER_H

#include <cstdint>
//#include "FpValueHolder.h"

namespace fp
{

class Potentiometer
{
public:
    enum TouchState
    {
        Released = 0,
        Touched = 1
    };
    struct Data
    {
        uint32_t   value;
        TouchState touchState;
    };
    class CallbackIf
    {
    public:
        virtual void onChanged(uint32_t value, const Widget& w) = 0;
        virtual void onTouchStateChanged(const Data& data, const Widget& w) = 0;
    };
    struct ValueHolder
    {
        void fireCallbacksAndReset(CallbackIf& cbIf, const Widget& w)
        {
            if(touchState.hasChanged())
            {
                cbIf.onTouchStateChanged({value.value(), touchState.value()}, w);
                touchState.resetState();
            }
            if(value.hasChanged())
            {
                cbIf.onChanged(value.value(), w);
                value.resetState();
            }
        }
        Value<uint32_t>   value;
        Value<TouchState> touchState;
    };
    class IProvider
    {
    public:
        virtual void registerCB(typename Potentiometer::CallbackIf& cb, const Widget& w) = 0;
        virtual void unRegisterCB(typename Potentiometer::CallbackIf& cb, const Widget& w) = 0;
    };
};



 
} // namespace fp
#endif