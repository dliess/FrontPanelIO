#include <gtest/gtest.h>
#include <vector>
#include "FpLedSceneHandler.h"

using namespace fp;

class TestLedTopology
{
public:
    enum Id{
        LedMatrix = 0,
        LedRow = 1,
        Led = 2,
        eLast    = Led
    };
   static constexpr Vector2d<uint8_t> getDim(Id widgetId)
   {
      constexpr Vector2d<uint8_t> dim[Id::eLast + 1] = { {8, 8}, {2, 1}, {1, 1} } ;
      return dim[widgetId];
   }
};

class TestLedScene : public LedSceneHandler<TestLedScene, TestLedTopology, 3>
{
public:
    TestLedScene() = default;
    struct WidgetAndColor
    {
        Widget        w;
        Led::ColorRGB color;
    };
    const std::vector<WidgetAndColor>& lastLedSetData() const noexcept { return m_data; };
    void clearData() { m_data.clear(); }
private:
    friend LedSceneHandler<TestLedScene, TestLedTopology>;
    void setLed(const Widget& w, const Led::ColorRGB& colorRGB) { m_data.push_back(WidgetAndColor({w, colorRGB})); };
    std::vector<WidgetAndColor> m_data;
};

class TestLedUser : public Led::ILedScene
{
public:
    void onGotRevealed(const Widget& w) final {};
    void onGotHidden(const Widget& w) final {};
};

TEST(FpLedSceneHandlerTest, setLedIfUnreservedTest) {
    TestLedScene testLedScene;
    TestLedUser  testLedUser1;
    constexpr Led::ColorRGB color1({255, 0, 0});
    const auto w1 = Widget(TestLedTopology::LedMatrix, IdxAll, IdxAll);

    testLedScene.setLedOfScene(&testLedUser1, w1, color1);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), 0);
}

TEST(FpLedSceneHandlerTest, reserveReleaseLedTest) {
    TestLedScene testLedScene;
    TestLedUser  testLedUser1;
    TestLedUser  testLedUser2;

    constexpr Led::ColorRGB color1({255, 0, 0});
    constexpr Led::ColorRGB color2({0, 255, 0});

    const auto w1 = Widget(TestLedTopology::LedMatrix, IdxAll, IdxAll);
    const auto w2 = Widget(TestLedTopology::LedMatrix, IdxAll, 3);

    testLedScene.reserveLed(&testLedUser1, w1, color1);
    const auto dim = TestLedTopology::getDim(TestLedTopology::Id(w1.id));
    ASSERT_EQ(testLedScene.lastLedSetData().size(), dim.x * dim.y);
    testLedScene.clearData();

    testLedScene.setLedOfScene(&testLedUser1, Widget(w1.id, IdxAll, 2), color2);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), dim.x);
    testLedScene.clearData();

    testLedScene.reserveLed(&testLedUser2, w2, color2);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), dim.x);
    testLedScene.clearData();

    testLedScene.setLedOfScene(&testLedUser1, Widget(w1.id, IdxAll, IdxAll), color2);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), (dim.x - 1) * dim.y);
    testLedScene.clearData();  

    testLedScene.releaseLed(&testLedUser2, w2);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), dim.x);
    testLedScene.clearData();
}

TEST(FpLedSceneHandlerTest, setNonReservedLedTest) {
    TestLedScene testLedScene;
    TestLedUser  testLedUser1;
    constexpr Led::ColorRGB color1({255, 0, 0});
    const auto wId = TestLedTopology::LedMatrix;
    const auto w = Widget(wId, IdxAll, IdxAll);
    testLedScene.setLedOfScene(&testLedUser1, w, color1);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), 0);
    testLedScene.clearData();
}

TEST(FpLedSceneHandlerTest, setNonActualLedTest) {
    TestLedScene testLedScene;
    TestLedUser  testLedUser1;
    TestLedUser  testLedUser2;

    constexpr Led::ColorRGB red({255, 0, 0});
    constexpr Led::ColorRGB green({0, 255, 0});

    const auto wId = TestLedTopology::LedMatrix;
    const auto w = Widget(wId, 2, 5);

    testLedScene.reserveLed(&testLedUser1, w, red);
    testLedScene.reserveLed(&testLedUser2, w, red);
    testLedScene.clearData();

    testLedScene.setLedOfScene(&testLedUser1, w, green);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), 0);

    testLedScene.releaseLed(&testLedUser2, w);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), 1);
    ASSERT_EQ(testLedScene.lastLedSetData()[0].color, green);
}

TEST(FpLedSceneHandlerTest, releaseNonActualLedTest) {
    TestLedScene testLedScene;
    TestLedUser  testLedUser1;
    TestLedUser  testLedUser2;
    TestLedUser  testLedUser3;

    constexpr Led::ColorRGB red({255, 0, 0});
    constexpr Led::ColorRGB green({0, 255, 0});

    const auto wId = TestLedTopology::LedMatrix;
    const auto w = Widget(wId, 2, 5);

    testLedScene.reserveLed(&testLedUser1, w, red);
    testLedScene.reserveLed(&testLedUser2, w, red);
    testLedScene.reserveLed(&testLedUser3, w, red);
    testLedScene.clearData();

    testLedScene.releaseLed(&testLedUser2, w);
    ASSERT_EQ(testLedScene.lastLedSetData().size(), 0);
}
