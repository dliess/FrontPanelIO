#include <gtest/gtest.h>
#include "FpTopologyContainer.h"
#include "FpVector2D.h"

using namespace fp;

class TestEmptyTopology
{
public:
    enum Id{
        eLast    = -1
    };
   static const Vector2d<uint8_t> &getDim(Id widgetId)
   {
      static const Vector2d<uint8_t> dim = {0,0};
      return dim;
   }
};
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
};

TEST(WidgetTopologyContainerTest, GetTest) {
    TopologyContainer<int, TestTopology> container;
    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(nullptr, container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(nullptr, container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 1))));

    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 0))));
    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 1))));
    ASSERT_EQ(nullptr, container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(nullptr, container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 2))));

    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 0))));
    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 0))));
    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1))));
    ASSERT_NE(nullptr, container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 1))));
    ASSERT_EQ(nullptr, container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 2))));
    ASSERT_EQ(nullptr, container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(2, 0))));

    *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))) = 10;
    ASSERT_EQ(10, *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));
}

TEST(WidgetTopologyContainerTest, EmptyTest) {
    TopologyContainer<int, TestEmptyTopology> emptyContainer;
    ASSERT_EQ(0, sizeof(emptyContainer));
    ASSERT_EQ(nullptr, emptyContainer.get(Widget(TestEmptyTopology::Id::eLast, Vector2d<uint8_t>(0, 0))));
}

class Visitor
{
public:
    Visitor(int val) : m_val(val) {}
    void operator()(int& val, const Widget& widget)
    {
        val = m_val;
    }
private:
    int m_val;
};

TEST(WidgetTopologyContainerTest, ForEachTest) {
    TopologyContainer<int, TestTopology> container;
    static const int VALUE = 1234;
    container.forEach(Visitor(VALUE));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));

    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 1))));

    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 1))));
}

TEST(WidgetTopologyContainerTest, ForWidgetTest) {
    TopologyContainer<int, TestTopology> container;
    Widget widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1));

    container.forEach(Visitor(0));
    static const int VALUE = 1234;
    container.forWidget(widget, Visitor(VALUE));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 1))));

    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1))));
    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 1))));

    container.forEach(Visitor(0));
    widget.coord.x = widget.coord.ALL;
    widget.coord.y = 1;
    container.forWidget(widget, Visitor(VALUE));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 1))));

    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 1))));

    container.forEach(Visitor(0));
    widget.coord.x = 0;
    widget.coord.y = widget.coord.ALL;
    container.forWidget(widget, Visitor(VALUE));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 1))));

    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1))));
    ASSERT_EQ(0,     *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 1))));

    container.forEach(Visitor(0));
    widget.coord.x = widget.coord.ALL;
    widget.coord.y = widget.coord.ALL;
    container.forWidget(widget, Visitor(VALUE));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget1, Vector2d<uint8_t>(0, 0))));

    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(0, *container.get(Widget(TestTopology::Id::Widget2, Vector2d<uint8_t>(0, 1))));

    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 0))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(0, 1))));
    ASSERT_EQ(VALUE, *container.get(Widget(TestTopology::Id::Widget3, Vector2d<uint8_t>(1, 1))));
}