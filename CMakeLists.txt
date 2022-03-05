cmake_minimum_required(VERSION 3.11)
 
project(FrontPanelIO 
        VERSION 0.0.1 
        LANGUAGES C CXX)

set (CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

include(CTest)
option(BUILD_TESTS "Build with unit-tests" ON)

add_subdirectory(FrontPanelUtils)
add_subdirectory(FrontPanelBase)
add_subdirectory(FrontPanelGfx)
add_subdirectory(FrontPanelDisplay)

if(BUILD_TESTS)
  enable_testing() 
  add_custom_target(UnitTests)
  add_dependencies(UnitTests runTestsFpBase runTestsFpDisplay)
endif()

install(EXPORT ${PROJECT_NAME}-targets
  NAMESPACE  ${PROJECT_NAME}::
  DESTINATION  "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

configure_file(cmake/${PROJECT_NAME}Config.cmake.in cmake/${PROJECT_NAME}Config.cmake @ONLY)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" COMPATIBILITY SameMajorVersion)
install(FILES 
           "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
           "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config-version.cmake" 
        DESTINATION 
           "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")