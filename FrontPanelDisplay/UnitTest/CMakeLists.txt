find_package(GTest REQUIRED)

set(SOURCES "UT_main.cpp"
            "UT_DoubleBufAnalyzer.cpp")
 
set(TARGET_NAME "runTestsFpDisplay")

add_executable(${TARGET_NAME} ${SOURCES})
target_link_libraries(${TARGET_NAME}
    PUBLIC
        GTest::GTest
        GTest::Main
        pthread
        FpUtils
        FpBase
        FpDisplay
)

add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
