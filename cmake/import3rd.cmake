
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyUi")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/QSystemModule")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixLogger")

if(ANDROID)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/JNIModule")
endif()

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    QSystemModule
    SonixLogger
)

# QML Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautyUiplugin
    $<$<PLATFORM_ID:Android>:JNIModule>
)
