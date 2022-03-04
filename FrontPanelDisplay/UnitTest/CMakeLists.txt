find_package(GTest REQUIRED)

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

