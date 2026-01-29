set(QT_QML_GENERATE_QMLLS_INI ON)

set_target_properties(${PROJECT_NAME} PROPERTIES
    QT_QML_COMPILE_SOURCES ON # 强制所有 QML 文件都被编译为 C++
    QT_QML_SOURCE_PROTECTION ON # 开启源码保护
    QT_QMLCACHEGEN_ARGUMENTS "--direct-calls" # "--direct-calls" "--verbose"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE "$<$<CONFIG:Release>:TRUE>$<$<NOT:$<CONFIG:Release>>:FALSE>"
    WIN32_EXECUTABLE "$<$<CONFIG:Debug>:FALSE>$<$<NOT:$<CONFIG:Debug>>:TRUE>"
)
