#ifndef FP_INPUT_CALLBACK_LAYER_H
#define FP_INPUT_CALLBACK_LAYER_H

#include "FpTopologyContainer.h"
#include "FpCallbackStack.h"

namespace fp
{

template<class WidgetType, class Topology>
class _InputCallbackLayer
{
public:
    typename WidgetType::ValueHolder* get(const Widget& w);
    const typename WidgetType::ValueHolder* get(const Widget& w) const;
    void checkValuesAndInvokeCallbacks(const Widget& w);
    void checkValuesAndInvokeCallbacks();
    void registerCB(typename WidgetType::CallbackIf& cb, const Widget& w);
    void unRegisterCB(typename WidgetType::CallbackIf& cb, const Widget& w);
private:
   using WidgetCbStack = CallbackStack< typename WidgetType::CallbackIf*, 8 >;
   TopologyContainer<WidgetCbStack, Topology>                    m_Callbacks;
   TopologyContainer<typename WidgetType::ValueHolder, Topology> m_values;
};

template<class WidgetType, class Topology>
typename WidgetType::ValueHolder* _InputCallbackLayer<WidgetType, Topology>::get(const Widget& w)
{
    return m_values.get(w);
}

template<class WidgetType, class Topology>
const typename WidgetType::ValueHolder* _InputCallbackLayer<WidgetType, Topology>::get(const Widget& w) const
{
    return m_values.get(w);
}

template<class WidgetType, class Topology>
void _InputCallbackLayer<WidgetType, Topology>::checkValuesAndInvokeCallbacks(const Widget& w)
{
    auto pValueHolder = m_values.get(w);
    if(pValueHolder)
    {
        auto cbIf = m_Callbacks.get(w)->getActual();
        if(cbIf)
        {
            pValueHolder->fireCallbacksAndReset(*cbIf.value(), w);
        }
    }
}

template<class WidgetType, class Topology>
void _InputCallbackLayer<WidgetType, Topology>::checkValuesAndInvokeCallbacks()
{
    m_values.forEach([this](typename WidgetType::ValueHolder& valueHolder, const Widget& w){
        auto cbIf = m_Callbacks.get(w)->getActual();
        if(cbIf)
        {
            valueHolder.fireCallbacksAndReset(*cbIf.value(), w);
        }
    });
}

template<class WidgetType, class Topology>
void _InputCallbackLayer<WidgetType, Topology>::registerCB(typename WidgetType::CallbackIf& cbIf, const Widget& w)
{
    m_Callbacks.forWidget(w, [&cbIf](WidgetCbStack& wCbStack, const Widget& w){
        wCbStack.pushBack(&cbIf);
    });
}

template<class WidgetType, class Topology>
void _InputCallbackLayer<WidgetType, Topology>::unRegisterCB(typename WidgetType::CallbackIf& cbIf, const Widget& w)
{
    m_Callbacks.forWidget(w, [&cbIf](WidgetCbStack& wCbStack, const Widget& w){
        wCbStack.remove(&cbIf);
    });
}

// Since Topology contains the widget Type
template <class Topology>
using InputCallbackLayer = _InputCallbackLayer<typename Topology::WidgetType, Topology>;

} // namespace fp
#endif