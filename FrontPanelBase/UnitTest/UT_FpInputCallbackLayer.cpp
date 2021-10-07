#include <gtest/gtest.h>
#include "FpInputCallbackLayer.h"
#include "FpEncoder.h"

using namespace fp;

class TestTopology
{
public:
    enum Id{
        Widget1 = 0,
        Widget2 = 1,
        Widget3 = 2,
        eLast    = Widget3
    };
   static const Vector2d<uint8_t> &getDim(Id widgetId)
   {
      static const Vector2d<uint8_t> dim[Id::eLast + 1] = { {1, 1}, {1, 2}, {2, 2} };
      return dim[widgetId];
   }
   using WidgetType = Encoder;
};

TEST(FpInputCallbackLayerTest, ForWidgetValueDoTest) {
    InputCallbackLayer<TestTopology> icl;
    icl.forWidgetValueDo(Widget(TestTopology::Widget1), [](Encoder::ValueHolder& valueHolder, const Widget& w){
        valueHolder.increments.set(2);
    });
}