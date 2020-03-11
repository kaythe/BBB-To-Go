cmake_minimum_required(VERSION 3.0.0)

#set(CMAKE_C_COMPILER "arm-buildroot-linux-uclibcgnueabihf-gcc-8.3.0")
#set(CMAKE_CXX_COMPILER "arm-buildroot-linux-uclibcgnueabihf-gcc-8.3.0")

project(LVGL-Test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(LVGL-Test main.cpp)
target_include_directories(LVGL-Test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/lvgl" "${CMAKE_CURRENT_SOURCE_DIR}/lvgl_drivers")
add_subdirectory(lvgl/src)
add_subdirectory(lv_drivers)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)