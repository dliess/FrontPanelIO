find_package(GTest REQUIRED)

set(SOURCES "UT_main.cpp"
            "UT_TopologyContainer.cpp"
            "UT_Increment.cpp"
            "UT_LedSceneHandler.cpp"
            "UT_Value.cpp"
            "UT_CallbackStack.cpp"
            "UT_FpInputCallbackLayer.cpp"
)
 
add_executable(runTestsFpBase ${SOURCES})
target_link_libraries(runTestsFpBase
    PUBLIC
        GTest::GTest
        GTest::Main
        pthread 
        FpUtils 
        FpBase
)