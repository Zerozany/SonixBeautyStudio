find_package(tomlplusplus CONFIG REQUIRED)
find_path(EXPRTK_INCLUDE_DIRS "exprtk.hpp")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    tomlplusplus::tomlplusplus
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${EXPRTK_INCLUDE_DIR}
)
