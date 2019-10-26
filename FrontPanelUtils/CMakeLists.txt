cmake_minimum_required(VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)

add_library(FpUtils INTERFACE)

target_include_directories(FpUtils INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}"
)
