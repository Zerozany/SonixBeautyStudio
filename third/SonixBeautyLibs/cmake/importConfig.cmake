target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/utf-8"
    )

    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/FS"
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
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
