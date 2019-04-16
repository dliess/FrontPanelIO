cmake_minimum_required(VERSION 2.6)

set (CMAKE_CXX_STANDARD 11)

add_library(FpGfx STATIC
    "FpRenderBase.cpp"
    "FpFontRenderer.cpp"
    "FpColorRGB.cpp"
)

target_include_directories(FpGfx PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
    "Fonts"
)

target_link_libraries(FpGfx PUBLIC FpUtils)