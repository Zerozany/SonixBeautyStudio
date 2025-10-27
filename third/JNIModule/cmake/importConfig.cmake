target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

if(MSVC)
    add_compile_options("/utf-8")
    add_compile_options("/FS")
endif()
