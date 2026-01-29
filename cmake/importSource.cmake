file(GLOB SOURCEFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src/**/*.h"
    "${CMAKE_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/**/*.hpp"
)

file(GLOB RESOURCESLIST RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/resource/*.png"
    "${CMAKE_SOURCE_DIR}/view/resource/**/*.png"
)

file(GLOB QFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/**/**/**/*.qml"
    "${CMAKE_SOURCE_DIR}/view/**/**/*.qml"
    "${CMAKE_SOURCE_DIR}/view/**/*.qml"
    "${CMAKE_SOURCE_DIR}/view/*.qml"
)

file(GLOB QMLSINGLETONS RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/global/*.qml"
)

set_source_files_properties(
    ${QMLSINGLETONS}
    PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    QML_FILES ${QFILES}
    SOURCES ${SOURCEFILES}
    RESOURCES ${RESOURCESLIST}
    DEPENDENCIES ${THIRDMODULE}
)

file(GLOB INCLUDEDIR "${CMAKE_SOURCE_DIR}/src/*")

foreach(HEADERDIR ${INCLUDEDIR})
    if(NOT IS_DIRECTORY ${HEADERDIR})
        continue()
    endif()

    target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERDIR})
endforeach()
