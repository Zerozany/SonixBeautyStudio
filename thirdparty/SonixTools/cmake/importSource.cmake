file(GLOB_RECURSE SOURCEFILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SOURCEFILES}
)

file(GLOB_RECURSE INCLUDEDIR LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
)

foreach(_DIR ${INCLUDEDIR})
    if(IS_DIRECTORY ${_DIR})
        target_include_directories(${PROJECT_NAME} PUBLIC ${_DIR})
    endif()
endforeach()
