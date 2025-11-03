file(GLOB SRCFILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRCFILES}
)

file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/*")

foreach(HEADERDIR ${INCLUDEDIR})
        if(NOT IS_DIRECTORY ${HEADERDIR})
                continue()
        endif()

        target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
endforeach()

target_include_directories(${PROJECT_NAME}
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
