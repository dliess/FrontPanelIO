add_subdirectory(UnitTest EXCLUDE_FROM_ALL)

set(TOPOLOGY_CODE_GEN_TOOL "${CMAKE_CURRENT_LIST_DIR}/Topology/WidgetCodeGenerator.py" PARENT_SCOPE)

set(TARGET_NAME "FpBase")

set(HEADERS
    "FpButton5d.h"
    "FpTouchSurface.h"
    "FpEncoder.h"
    "FpLedSceneHandler.h"
    "FpValue.h"
    "FpButton.h"
    "FpIncrement.h"
    "FpWidget.h"
    "FpPositioner.h"
    "FpPotentiometer.h"
    "FpTopologyContainer.h"
    "FpLed.h"
    "FpCallbackStack.h"
    "FpInputCallbackLayer.h"
    "FpButton3d.h"
)

add_library(${TARGET_NAME} INTERFACE)

target_include_directories(${TARGET_NAME}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
    "$<BUILD_INTERFACE:${TOPOLOGY_DIR}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>"
)

target_link_libraries(${TARGET_NAME} INTERFACE FpUtils)

target_compile_options(${TARGET_NAME} INTERFACE -Wno-zero-length-array)

set_target_properties(${TARGET_NAME} PROPERTIES
    PUBLIC_HEADER "${HEADERS}"
)

install(TARGETS ${TARGET_NAME}  EXPORT ${PROJECT_NAME}-targets
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)
