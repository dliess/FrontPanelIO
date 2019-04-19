cmake_minimum_required(VERSION 3.8)

set (CMAKE_CXX_STANDARD 11)

add_subdirectory(UnitTest EXCLUDE_FROM_ALL)
 
add_library(FpDisplay STATIC
    "FpDoubleBufAnalyzer.cpp"
    "FpFrameBufRenderer.cpp"
)
target_include_directories(FpDisplay PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(FpDisplay PUBLIC FpBase FpGfx)
