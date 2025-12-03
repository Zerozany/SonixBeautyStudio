add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroSystem")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyUI")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixBeautyKits")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroLibs")

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    QZeroSystem

    # SonixBeautyUI

    # SonixBeautyKits

    # QZeroLibs
)

# QML Static Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
)

# QML Shared Module
# list(APPEND THIRDMODULE QZeroSystem SonixBeautyUI SonixBeautyKits)
list(APPEND THIRDMODULE QZeroSystem)
