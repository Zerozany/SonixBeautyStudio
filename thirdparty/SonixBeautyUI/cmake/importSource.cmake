file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
)

file(GLOB QMLFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
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

qt_add_qml_module(${PROJECT_NAME}
    URI "${PROJECT_NAME}"
    VERSION 1.0
    QML_FILES ${QMLFILES} ${QMLSINGLETONS}
    SOURCES ${SRCFILES}
)

file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(HEADERDIR ${INCLUDEDIR})
    if(NOT IS_DIRECTORY ${HEADERDIR})
        continue()
    endif()

    target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
endforeach()
