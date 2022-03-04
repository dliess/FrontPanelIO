add_library(FpGfx STATIC
    "FpRenderBase.cpp"
    "FpFontRenderer.cpp"
)

target_include_directories(FpGfx PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
    "Fonts"
)

target_link_libraries(FpGfx PUBLIC FpUtils)

option(__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__ "use opengl/es-style color representation" OFF)
if(${__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__})
   target_compile_definitions(FpGfx PUBLIC "__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__")
endif(${__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__})
