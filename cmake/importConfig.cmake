target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/utf-8"
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

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin"

        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib"
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )
endif()
