if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    )

    target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRCFILES}
    )

    set(QT_QML_GENERATE_QMLLS_INI ON)

    qt_add_qml_module(${PROJECT_NAME}
        URI "${PROJECT_NAME}"
        VERSION 1.0
        RESOURCE_PREFIX "/"
        QML_FILES
        SOURCES ${SRCFILES}
        OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qmlimports/${PROJECT_NAME}"
    )

    file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

    foreach(HEADERDIR ${INCLUDEDIR})
        if(NOT IS_DIRECTORY ${HEADERDIR})
            continue()
        endif()

        target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
    endforeach()
endif()
