if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    )

    file(GLOB INCLUDEDIR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
    )

    foreach(HEADERDIR ${INCLUDEDIR})
        if(IS_DIRECTORY ${HEADERDIR})
            target_include_directories(${PROJECT_NAME}
                PUBLIC
                ${HEADERDIR}
            )
        endif()
    endforeach()

    qt_add_qml_module(${PROJECT_NAME}
        URI "${PROJECT_NAME}"
        VERSION 1.0
        RESOURCE_PREFIX "/"
        SOURCES ${SRCFILES}
        OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qmlimports/${PROJECT_NAME}"
    )
endif()
