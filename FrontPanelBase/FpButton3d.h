#ifndef FP_BUTTON3D_H
#define FP_BUTTON3D_H

#include <cstdint>
#include <FpValue.h>

namespace fp
{
struct Widget;
}

namespace fp
{

class Button3d
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
    
    class CallbackIf
    {
    public:
        virtual void onPressStateChange(const StateData& data, const Widget& w) = 0;
        virtual void onPositionEvents(const uint32_t& pressure, const Widget& w) = 0;
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
                cbIf.onPositionEvents(pressure.value(), w);
                pressure.resetState();
            }
        }
        Value<PressState> pressState;
        uint32_t velocity;
        Value<uint32_t>   pressure;
    };
    class IProvider
    {
    public:
        virtual void registerCB(typename Button3d::CallbackIf& cb, const Widget& w) = 0;
    };
};



 
} // namespace fp
#endif