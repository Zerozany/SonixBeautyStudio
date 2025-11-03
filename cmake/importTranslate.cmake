qt_standard_project_setup(
    I18N_TRANSLATED_LANGUAGES en zh_CN
)

qt_add_translations(
    ${PROJECT_NAME}
    TS_FILE_DIR ${CMAKE_SOURCE_DIR}/translate
    TS_FILE_BASE ${PROJECT_NAME}
    RESOURCE_PREFIX /translate
    QM_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/translate"
)

file(GLOB QM_FILES
    "${CMAKE_BINARY_DIR}/translate/${PROJECT_NAME}_*.qm"
)

qt_add_resources(${PROJECT_NAME} "translations"
    PREFIX "/translate"
    BASE "${CMAKE_BINARY_DIR}/translate"
    FILES ${QM_FILES}
)

add_dependencies(${PROJECT_NAME} update_translations)
add_dependencies(${PROJECT_NAME} release_translations)
