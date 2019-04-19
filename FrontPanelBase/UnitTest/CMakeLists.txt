cmake_minimum_required(VERSION 3.8)
 
# Locate GTest
find_package(GTest REQUIRED)

set (CMAKE_CXX_STANDARD 11)

set(SOURCES "UT_main.cpp"
            "UT_TopologyContainer.cpp"
            "UT_Increment.cpp"
            "UT_Value.cpp"
            "UT_CallbackStack.cpp")
set(INCLUDE_DIRS
    "${GTEST_INCLUDE_DIRS}")
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTestsFpBase ${SOURCES})
target_include_directories(runTestsFpBase PRIVATE ${INCLUDE_DIRS})
target_link_libraries(runTestsFpBase ${GTEST_LIBRARIES} pthread FpUtils FpBase)

