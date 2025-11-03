add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyUI")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyKits")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyLibs")

if(ANDROID)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyJNI")
endif()

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautyKits
    SonixBeautyLibs
    $<$<PLATFORM_ID:Android>:SonixBeautyJNI>
)

# QML Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautyUIplugin
    $<$<PLATFORM_ID:Android>:SonixBeautyJNIplugin>
)
