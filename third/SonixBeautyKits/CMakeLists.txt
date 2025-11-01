cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(SonixBeautyKits VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

include("${CMAKE_SOURCE_DIR}/cmake/importConfig.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/importSource.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/import3rd.cmake")
