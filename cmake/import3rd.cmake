add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroSystem")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroZanyUI")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroAssistKit")

# add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroPackage")

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    QZeroSystem
    QZeroZanyUI
    QZeroAssistKit

    # QZeroPackage
)

# QML Static Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
)

# QML Shared Module
list(APPEND THIRDMODULE QZeroSystem QZeroZanyUI QZeroAssistKit)

# list(APPEND THIRDMODULE QZeroSystem QZeroZanyUI)
set(QML_IMPORT_PATH "${PROJECT_BINARY_DIR}/thirdparty" CACHE PATH "" FORCE)
