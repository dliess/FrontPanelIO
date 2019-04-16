#include "FpDoubleBufAnalyzer.h"
#include "FpFrameBuffer.h"
#include "FpColorRGB.h"
#include "FpGfxTypes.h"
#include <gtest/gtest.h>
#include <vector>

using namespace fp;

class DoubleBufAnalyzerTest : public ::testing::Test {
 protected:
 DoubleBufAnalyzerTest() : 
    resolution(10,10),
    actualFrameBuf(resolution),
    prevFrameBuf(resolution),
    analyzer(actualFrameBuf, prevFrameBuf)
    {}

        void SetUp() override {
        actualFrameBuf.clear();
        prevFrameBuf.clear();
    }
   // void TearDown() override {}

    void _PixelDifferenceTest(const std::vector<gfx::Coord>& pixCoords)
    {
        ASSERT_TRUE(pixCoords.size() > 0);
        const auto expectedNumChangedPix = pixCoords.size();
        gfx::Coord upperLeft(pixCoords[0]);
        gfx::Coord lowerRight(pixCoords[0]);
        for(auto&& p : pixCoords)
        {
            upperLeft.x = std::min(upperLeft.x, p.x);
            upperLeft.y = std::min(upperLeft.y, p.y);
            lowerRight.x = std::max(lowerRight.x, p.x);
            lowerRight.y = std::max(lowerRight.y, p.y);
        }
        const gfx::Pixel area = (lowerRight.x - upperLeft.x + 1) * 
                                         (lowerRight.y - upperLeft.y + 1);

        actualFrameBuf.clear();
        prevFrameBuf.clear();

        for(auto&& p : pixCoords)
        {
            actualFrameBuf.at(p) = ColorRGB(1,1,1);     
        }
        analyzer.analyze();
        ASSERT_EQ(expectedNumChangedPix, analyzer.getNumDiffPixels());
        ASSERT_EQ(upperLeft, analyzer.diffArea().upperLeft);
        ASSERT_EQ(lowerRight, analyzer.diffArea().lowerRight);

        actualFrameBuf.clear();
        prevFrameBuf.clear();

        for(auto&& p : pixCoords)
        {
            prevFrameBuf.at(p) = ColorRGB(1,1,1);     
        }

        analyzer.analyze();
        ASSERT_EQ(expectedNumChangedPix, analyzer.getNumDiffPixels());
        ASSERT_EQ(upperLeft, analyzer.diffArea().upperLeft);
        ASSERT_EQ(lowerRight, analyzer.diffArea().lowerRight);
    }

    gfx::Resolution    resolution;
    DisplayFrameBuffer actualFrameBuf;
    DisplayFrameBuffer prevFrameBuf;
    DoubleBufAnalyzer  analyzer;
};

TEST_F(DoubleBufAnalyzerTest, NoDifferenceTest) {
    analyzer.analyze();
    ASSERT_EQ(false, analyzer.getNumDiffPixels());


    actualFrameBuf.at(0,0) = ColorRGB(1,1,1);
    prevFrameBuf.at(0,0)   = ColorRGB(1,1,1);

    analyzer.analyze();
    ASSERT_EQ(false, analyzer.getNumDiffPixels());

    actualFrameBuf.at(9,0) = ColorRGB(1,1,1);
    prevFrameBuf.at(9,0)   = ColorRGB(1,1,1);

    analyzer.analyze();
    ASSERT_EQ(false, analyzer.getNumDiffPixels());

    actualFrameBuf.at(9,9) = ColorRGB(1,1,1);
    prevFrameBuf.at(9,9)   = ColorRGB(1,1,1);

    analyzer.analyze();
    ASSERT_EQ(false, analyzer.getNumDiffPixels());
}

TEST_F(DoubleBufAnalyzerTest, OnePixelDifferenceTest) {
    const auto lastPixelX = resolution.x-1;
    const auto lastPixelY = resolution.y-1;

    _PixelDifferenceTest({{4,4}});
    _PixelDifferenceTest({{0,0}});
    _PixelDifferenceTest({{0,lastPixelY}});
    _PixelDifferenceTest({{lastPixelX,0}});
    _PixelDifferenceTest({{lastPixelX,lastPixelY}});
}

TEST_F(DoubleBufAnalyzerTest, MultiplePixelDifferenceTest) {
    const auto lastPixelX = resolution.x-1;
    const auto lastPixelY = resolution.y-1;

    _PixelDifferenceTest({{4,4}, {0,0}});
    _PixelDifferenceTest({{0,0}, {lastPixelX, lastPixelY}});
    _PixelDifferenceTest({{lastPixelX,0}, {0, lastPixelY}});
    _PixelDifferenceTest({{0,lastPixelY}, {lastPixelX, 0}});
    _PixelDifferenceTest({{lastPixelX, lastPixelY}, {0,0}});

    _PixelDifferenceTest({{0,0}, {lastPixelX, lastPixelY}, {4,4}});
    _PixelDifferenceTest({{lastPixelX,0}, {0, lastPixelY}, {4,4}});
    _PixelDifferenceTest({{0,lastPixelY}, {lastPixelX, 0}, {4,4}});
    _PixelDifferenceTest({{lastPixelX, lastPixelY}, {0,0}, {4,4}});

    _PixelDifferenceTest({{2,4}, {2,7}});
}
