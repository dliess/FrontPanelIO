cmake_minimum_required(VERSION 3.8)
 
set (CMAKE_CXX_STANDARD 17)

project(ClientHelper VERSION 0.0.1 LANGUAGES C CXX)

add_subdirectory(FrontPanelUtils)
add_subdirectory(FrontPanelBase)
add_subdirectory(FrontPanelGfx)
add_subdirectory(FrontPanelDisplay)

add_custom_target(UnitTests)
add_dependencies(UnitTests runTestsFpBase runTestsFpDisplay)