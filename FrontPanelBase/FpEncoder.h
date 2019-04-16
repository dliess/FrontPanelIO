#ifndef FP_ENCODER_H
#define FP_ENCODER_H

#include <cstdint>
#include "FpIncrement.h"
#include "FpValue.h"

namespace fp
{
class Widget;
}

namespace fp
{

class Encoder
{
public:
    enum TouchState
    {
        Released = 0,
        Touched = 1
    };
    class CallbackIf
    {
    public:
        virtual void onIncrement(int32_t data, const Widget& w) = 0;
        virtual void onTouchStateChanged(TouchState touchState, const Widget& w) = 0;
    };
    struct ValueHolder
    {
        void fireCallbacksAndReset(CallbackIf& cbIf, const Widget& w)
        {
            if(increments.hasChanged())
            {
                cbIf.onIncrement(increments.value(), w);
                increments.resetState();
            }
            if(touchState.hasChanged())
            {
                cbIf.onTouchStateChanged(touchState.value(), w);
                touchState.resetState();
            }
        }    
        Increment<int32_t> increments;
        Value<TouchState> touchState;
    };
    class IProvider
    {
    public:
        virtual void registerCB(Encoder::CallbackIf& cb, const Widget& w) = 0;
    };
};
 



} // namespace fp
#endif