find_package(spdlog CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    spdlog::spdlog
)
