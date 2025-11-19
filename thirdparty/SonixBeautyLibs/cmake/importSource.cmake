file(GLOB SOURCEFILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

target_sources(${PROJECT_NAME}
    PRIVATE
    ${SOURCEFILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
