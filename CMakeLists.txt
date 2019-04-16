cmake_minimum_required(VERSION 2.6)
 
set (CMAKE_CXX_STANDARD 11)

project(ClientHelper C CXX)

add_subdirectory(FrontPanelUtils)
add_subdirectory(FrontPanelBase)
add_subdirectory(FrontPanelGfx)
add_subdirectory(FrontPanelDisplay)

add_custom_target(UnitTests)
add_dependencies(UnitTests runTestsFpBase runTestsFpDisplay)