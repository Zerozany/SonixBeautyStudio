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

    target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRCFILES}
    )
endif()
