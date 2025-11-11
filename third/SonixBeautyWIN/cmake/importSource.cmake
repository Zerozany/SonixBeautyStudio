if(WIN32)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    )

    qt_add_qml_module(${PROJECT_NAME}
        URI "${PROJECT_NAME}"
        VERSION 1.0
        RESOURCE_PREFIX "/qt/qml"
        QML_FILES
        SOURCES ${SRCFILES}

        # NO_CACHEGEN
    )

    file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

    foreach(HEADERDIR ${INCLUDEDIR})
        if(NOT IS_DIRECTORY ${HEADERDIR})
            continue()
        endif()

        target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
    endforeach()

    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()
