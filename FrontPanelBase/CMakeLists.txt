cmake_minimum_required(VERSION 2.6)

add_subdirectory(UnitTest EXCLUDE_FROM_ALL)

set (CMAKE_CXX_STANDARD 11)

set(TOPOLOGY_CODE_GEN_TOOL "${CMAKE_CURRENT_LIST_DIR}/Topology/WidgetCodeGenerator.py" PARENT_SCOPE)

add_library(FpBase INTERFACE)

target_include_directories(FpBase INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${TOPOLOGY_DIR}"
)

target_link_libraries(FpBase INTERFACE FpUtils)