if(ANDROID)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/**/*.cpp"
    )

    file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/JNI/*")

elseif(WIN32)
    file(GLOB SRCFILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/**/*.cpp"
    )

    file(GLOB INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/src/WIN/*")
endif()

qt_add_qml_module(${PROJECT_NAME}
    URI "${PROJECT_NAME}"
    VERSION 1.0
    QML_FILES
    SOURCES ${SRCFILES}
)

foreach(HEADERDIR ${INCLUDEDIR})
    if(NOT IS_DIRECTORY ${HEADERDIR})
        continue()
    endif()

    target_include_directories(${PROJECT_NAME} PUBLIC ${HEADERDIR})
endforeach()
