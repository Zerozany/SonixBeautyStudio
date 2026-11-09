cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${PROJECT_NAME}
    VERSION 1.0.0
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} SHARED)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/import3rd.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/importSource.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/importConfig.cmake")
