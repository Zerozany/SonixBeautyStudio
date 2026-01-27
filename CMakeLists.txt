cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

project(SonixBeautyStudio VERSION 1.0.0 LANGUAGES CXX)

include("${CMAKE_SOURCE_DIR}/cmake/importQt.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/importConfig.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/import3rd.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/importSource.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/importTranslate.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/importPack.cmake")
