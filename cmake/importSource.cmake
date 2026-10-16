file(GLOB_RECURSE SOURCEFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/src/*.h"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.hpp"
)

file(GLOB_RECURSE RESOURCESLIST RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/*.png"
)

file(GLOB_RECURSE QFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/*.qml"
)

file(GLOB QMLSINGLETONS RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/view/public/Singleton/*.qml"
)

file(GLOB CONFIGFILES RELATIVE ${CMAKE_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/qtquickcontrols2.conf"
    "${CMAKE_SOURCE_DIR}/config/dataBase/*.db"
    "${CMAKE_SOURCE_DIR}/config/Android/*.pem"
    "${CMAKE_SOURCE_DIR}/config/settings/*.ini"
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
    DEPENDENCIES TARGET ${QMLMODULELIST}
)

qt_add_resources(${PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
    ${CONFIGFILES}
)

file(GLOB_RECURSE INCLUDEDIR LIST_DIRECTORIES true
    "${CMAKE_SOURCE_DIR}/src/*"
)

foreach(_DIR ${INCLUDEDIR})
    if(IS_DIRECTORY ${_DIR})
        target_include_directories(${PROJECT_NAME} PUBLIC ${_DIR})
    endif()
endforeach()
