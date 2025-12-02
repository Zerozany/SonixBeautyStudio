add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautySystem")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyUI")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyKits")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyLibs")

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SonixBeautySystem

    # SonixBeautyUI

    # SonixBeautyKits

    # SonixBeautyLibs
)

# QML Static Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
)

# QML Shared Module
# list(APPEND THIRDMODULE SonixBeautySystem SonixBeautyUI SonixBeautyKits)
list(APPEND THIRDMODULE SonixBeautySystem)
