cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)

set (CMAKE_CXX_STANDARD 11)

set(SOURCES "UT_main.cpp"
            "UT_DoubleBufAnalyzer.cpp")
set(INCLUDE_DIRS
    "${GTEST_INCLUDE_DIRS}")
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTestsFpDisplay ${SOURCES})
target_include_directories(runTestsFpDisplay PRIVATE ${INCLUDE_DIRS})
target_link_libraries(runTestsFpDisplay ${GTEST_LIBRARIES} pthread FpUtils FpBase FpDisplay)

