add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroSystem" "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/qml/QZeroSystem")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroMaterialUI" "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/qml/QZeroMaterialUI")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/QZeroAssistKit" "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/qml/QZeroAssistKit")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/ZeroPackage")
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/SonixTools")

# Qt/QML Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    QZeroSystem
    QZeroMaterialUI
    QZeroAssistKit
)

# cpp Module
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ZeroPackage
    SonixTools
)

# QML Shared Module List
list(APPEND QMLMODULELIST QZeroSystem QZeroMaterialUI QZeroAssistKit)
