find_package(GTest REQUIRED)

set(SOURCES "UT_main.cpp"
            "UT_TopologyContainer.cpp"
            "UT_Increment.cpp"
            "UT_LedSceneHandler.cpp"
            "UT_Value.cpp"
            "UT_CallbackStack.cpp"
            "UT_FpInputCallbackLayer.cpp"
)
 
set(TARGET_NAME "runTestsFpBase")

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME}
    PUBLIC
        GTest::GTest
        GTest::Main
        pthread 
        FpUtils 
        FpBase
)

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})