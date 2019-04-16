cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

add_library(FpUtils INTERFACE)

target_include_directories(FpUtils INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}"
)
