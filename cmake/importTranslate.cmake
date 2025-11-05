qt_standard_project_setup(
    I18N_TRANSLATED_LANGUAGES en zh_CN
)

add_dependencies(${PROJECT_NAME}
    update_translations
)

qt_add_translations(
    ${PROJECT_NAME}
    TS_FILE_DIR "${CMAKE_SOURCE_DIR}/translate"
    QM_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/translate"
    QM_FILES_OUTPUT_VARIABLE QM_FILES
    IMMEDIATE_CALL
)

qt_add_resources(${PROJECT_NAME} "translations"
    PREFIX "/translate"
    FILES ${QM_FILES}
    BASE "${CMAKE_BINARY_DIR}/translate"
)
