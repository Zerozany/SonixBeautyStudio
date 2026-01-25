target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

set(QT_QML_GENERATE_QMLLS_INI ON)

set_target_properties(${PROJECT_NAME} PROPERTIES
    QT_QML_COMPILE_SOURCES ON # 强制所有 QML 文件都被编译为 C++
    QT_QML_SOURCE_PROTECTION ON # 开启源码保护
    QT_QMLCACHEGEN_ARGUMENTS "--direct-calls" # "--direct-calls" "--verbose"
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "$<$<CXX_COMPILER_ID:MSVC>:/Z7>"
    )

    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/utf-8"
        "/FS"
    )

    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "$<$<CONFIG:Debug>:/Od>"
        "$<$<CONFIG:Release>:/Ox>"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        "-fdiagnostics-color=always" # 彩色输出诊断信息
        "-Wall" # 开启大部分警告
        "-Wextra" # 更多警告
        "$<$<CONFIG:Debug>:-O0>" # Debug 禁用优化
        "$<$<CONFIG:Release>:-O3>" # Release 最大优化
    )
endif()
