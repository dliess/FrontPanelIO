#ifndef FP_BUTTON_H
#define FP_BUTTON_H

#include <cstdint>
#include <FpValue.h>

namespace fp
{
struct Widget;
}

namespace fp
{

class Button
{
public:
    enum PressState
    {
        Released = 0,
        Pressed
    };
    class CallbackIf
    {
    public:
        virtual void onPressStateChange(const PressState& pressState, const Widget& w) = 0;
    };
    struct ValueHolder
    {
        void fireCallbacksAndReset(CallbackIf& cbIf, const Widget& w)
        {
            if(pressState.hasChanged())
            {
                cbIf.onPressStateChange(pressState.value(), w);
                pressState.resetState();
            }
        }
        Value<PressState> pressState;
    };

    class IProvider
    {
    public:
        virtual void registerCB(typename Button::CallbackIf& cb, const Widget& w) = 0;
        virtual void unRegisterCB(typename Button::CallbackIf& cb, const Widget& w) = 0;
    };
};


 
} // namespace fp
#endif