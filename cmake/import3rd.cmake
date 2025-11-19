# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyUI")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyKits")
# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyLibs")
if(ANDROID)
    add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyJNI")
elseif(WIN32)
    add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyWIN")
endif()

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE

    # SonixBeautyUI

    # SonixBeautyKits

    # SonixBeautyLibs
    $<$<PLATFORM_ID:Windows>:SonixBeautyWIN>
    $<$<PLATFORM_ID:Android>:SonixBeautyJNI>
)

# QML Static Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE

    # SonixBeautyKitsplugin
    # $<$<PLATFORM_ID:Android>:SonixBeautyJNIplugin>
)

# QML Shared Module
set(THIRDMODULE)

if(ANDROID)
    list(APPEND THIRDMODULE SonixBeautyJNI)
elseif(WIN32)
    list(APPEND THIRDMODULE SonixBeautyWIN)
endif()
