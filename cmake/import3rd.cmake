
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyUi")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/QSystemModule")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixLogger")

if(ANDROID)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/android")
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautyUiplugin
    QSystemModule
    SonixLogger
    $<$<PLATFORM_ID:Android>:JNIModuleplugin>
)
