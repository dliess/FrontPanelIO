if(BUILD_TESTS)
    add_subdirectory(UnitTest EXCLUDE_FROM_ALL)
endif()

set(TARGET_NAME "FpDisplay")

set(SOURCES
    "FpDoubleBufAnalyzer.cpp"
    "FpFrameBufRenderer.cpp"
)

set(HEADERS
    "FpFrameBufRenderer.h"
    "FpRenderSwitch.h"
    "FpIRenderMedium.h"
    "FpDisplayHandler.h"
    "FpDoubleBufAnalyzer.h"
    "FpDoubleBufHandler.h"
    "FpDisplayFrameBuffer.h"
    "FpRenderCbIf.h"
    "FpRenderSwitch.tcc"
    "FpDoubleBufHandler.tcc"
    "FpDisplayHandler.tcc"
)

add_library(${TARGET_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${TARGET_NAME} 
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_link_libraries(${TARGET_NAME} PUBLIC FpBase FpGfx)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}  EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)