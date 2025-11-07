file(GLOB SRCLIST RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

file(GLOB QFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/view/content/*.qml"
    "${CMAKE_CURRENT_SOURCE_DIR}/view/content/**/*.qml"
)

file(GLOB QMLSINGLETONS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/view/global/*.qml"
)

set_source_files_properties(
    ${QMLSINGLETONS}
    PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SRCLIST}
)

set(QT_QML_GENERATE_QMLLS_INI ON)

qt_add_qml_module(${PROJECT_NAME}
    URI "${PROJECT_NAME}"
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES ${QFILES} ${QMLSINGLETONS}
    SOURCES ${SRCLIST}
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qmlimports/${PROJECT_NAME}"
)

file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(HEADERDIR ${INCLUDEDIR})
    if(NOT IS_DIRECTORY ${HEADERDIR})
        continue()
    endif()

    target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
endforeach()
