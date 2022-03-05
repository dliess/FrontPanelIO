set(TARGET_NAME "FpGfx")

set(SOURCES
    "FpRenderBase.cpp"
    "FpFontRenderer.cpp"
)

set(HEADERS
    "FpRenderBase.h"
    "FpFrameBuffer.h"
    "FpFrameBuffer.tcc"
    "FpColorRGB.h"
    "FpColorRGB.tcc"
    "FpFont.h"
    "FpFontRenderer.h"
    "FpRenderIf.h"
    "FpGfxTypes.h"
    "FpIRender.h"
    "Fonts/DefaultMonospace.h"
)

add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME}
  PUBLIC
   "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
   "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Fonts>"
   "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_link_libraries(${TARGET_NAME} PUBLIC FpUtils)

option(__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__ "use opengl/es-style color representation" OFF)
if(${__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__})
   target_compile_definitions(${TARGET_NAME} PUBLIC "__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__")
endif(${__FP_COLOR_REPRESENTATION_EMBEDDED_STYLE__})

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}  EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)