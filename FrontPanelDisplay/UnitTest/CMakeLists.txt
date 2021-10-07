cmake_minimum_required(VERSION 3.8)
 
find_package(GTest REQUIRED)

set (CMAKE_CXX_STANDARD 17)

set(SOURCES "UT_main.cpp"
            "UT_DoubleBufAnalyzer.cpp")
 
add_executable(runTestsFpDisplay ${SOURCES})
target_link_libraries(runTestsFpDisplay
    PUBLIC
        GTest::GTest
        GTest::Main
        pthread
        FpUtils
        FpBase
        FpDisplay
)

