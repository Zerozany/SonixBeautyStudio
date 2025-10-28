if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
    )

    target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRCFILES}
    )

    file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

    file(GLOB INCLUDEDIR "${CMAKE_SOURCE_DIR}/src/*")

    foreach(HEADERDIR ${INCLUDEDIR})
        if(NOT IS_DIRECTORY ${HEADERDIR})
            continue()
        endif()

        target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
    endforeach()
endif()
