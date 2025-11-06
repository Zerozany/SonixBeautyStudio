add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyUI")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyKits")
add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyLibs")

if(ANDROID)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyJNI")
elseif(WIN32)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyWIN")
endif()

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautyKits
    SonixBeautyLibs
    $<$<PLATFORM_ID:WIN32>:SonixBeautyWIN>
    $<$<PLATFORM_ID:Android>:SonixBeautyJNI>
)

# QML Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautyUIplugin
    SonixBeautyKitsplugin
    $<$<PLATFORM_ID:WIN32>:SonixBeautyWINplugin>
    $<$<PLATFORM_ID:Android>:SonixBeautyJNIplugin>
)
