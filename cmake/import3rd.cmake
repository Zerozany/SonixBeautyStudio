add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyUI")

# add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyKits")
# add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyLibs")
if(ANDROID)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyJNI")
elseif(WIN32)
    add_subdirectory("${CMAKE_SOURCE_DIR}/third/SonixBeautyWIN")
endif()

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE

    SonixBeautyUI

    # SonixBeautyKits

    # SonixBeautyLibs
    $<$<PLATFORM_ID:Windows>:SonixBeautyWIN>

    # $<$<PLATFORM_ID:Android>:SonixBeautyJNI>
)

# QML Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE

    # SonixBeautyKitsplugin
    # $<$<PLATFORM_ID:Android>:SonixBeautyJNIplugin>
)
