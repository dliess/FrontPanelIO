cmake_minimum_required(VERSION 3.8)
 
set (CMAKE_CXX_STANDARD 11)

set(SOURCES "UT_main.cpp"
            "UT_TopologyContainer.cpp"
            "UT_Increment.cpp"
            "UT_Value.cpp"
            "UT_CallbackStack.cpp")
 
add_executable(runTestsFpBase ${SOURCES})
target_link_libraries(runTestsFpBase gtest pthread FpUtils FpBase)

