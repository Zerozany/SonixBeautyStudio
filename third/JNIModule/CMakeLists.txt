cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(JNIModule
    VERSION 1.0.0
    LANGUAGES CXX
)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/importQt.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/importConfig.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/importSource.cmake")
