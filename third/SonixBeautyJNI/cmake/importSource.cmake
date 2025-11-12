if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    )

    qt_add_qml_module(${PROJECT_NAME}
        URI "${PROJECT_NAME}"
        VERSION 1.0
        RESOURCE_PREFIX "/qt/qml"
        QML_FILES
        SOURCES ${SRCFILES}
    )

    file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

    foreach(HEADERDIR ${INCLUDEDIR})
        if(NOT IS_DIRECTORY ${HEADERDIR})
            continue()
        endif()

        target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
    endforeach()
endif()
