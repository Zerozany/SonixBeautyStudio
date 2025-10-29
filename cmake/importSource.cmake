file(GLOB SOURCEFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src/**/*.h"
    "${CMAKE_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/**/*.hpp"
)

file(GLOB QFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/**/**/*.qml"
    "${CMAKE_SOURCE_DIR}/view/**/*.qml"
    "${CMAKE_SOURCE_DIR}/view/*.qml"
)

file(GLOB RESOURCES_LIST RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/resource/*.png"
    "${CMAKE_SOURCE_DIR}/view/resource/**/*.png"
)

qt_add_resources(${PROJECT_NAME} "Main"
    PREFIX "/"
    FILES
    ${RESOURCES_LIST}
)

set(QT_QML_GENERATE_QMLLS_INI ON)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION 1.0
    RESOURCE_PREFIX "/"
    QML_FILES ${QFILES}
    SOURCES ${SOURCEFILES}
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qmlimports/${PROJECT_NAME}"
)

file(GLOB INCLUDEDIR "${CMAKE_SOURCE_DIR}/src/*")

foreach(HEADERDIR ${INCLUDEDIR})
    if(NOT IS_DIRECTORY ${HEADERDIR})
        continue()
    endif()

    target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERDIR})
endforeach()
