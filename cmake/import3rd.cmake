add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroSystem")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroMaterialUI")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroAssistKit")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroPackage")

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    QZeroSystem
    QZeroMaterialUI
    QZeroAssistKit
    QZeroPackage
)

# QML Static Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
)

# QML Shared Module List
list(APPEND QMLMODULELIST QZeroSystem QZeroMaterialUI QZeroAssistKit)
