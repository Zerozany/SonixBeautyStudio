if(WIN32)
    get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)

    if(TARGET_TYPE STREQUAL "EXECUTABLE")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "$ENV{Qt6_BIN_DIR}/windeployqt.exe"
            $<$<CONFIG:Debug>:--debug>
            $<$<CONFIG:Release>:--release>
            --qmldir "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
            "$<TARGET_FILE:${PROJECT_NAME}>"
            COMMENT "Deploying Qt dependencies for ${PROJECT_NAME}"
        )

        # 安装步骤
        foreach(QMLMODULE IN LISTS QMLMODULELIST)
            install(FILES
                "${CMAKE_BINARY_DIR}/thirdparty/${QMLMODULE}/${QMLMODULE}plugin.dll"
                "${CMAKE_BINARY_DIR}/thirdparty/${QMLMODULE}/qmldir"
                DESTINATION "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/qml/${QMLMODULE}"
            )
        endforeach()
    else()
        message(STATUS "skip windeployqt: ${PROJECT_NAME} It is not an executable file")
    endif()
elseif(ANDROID)
    # 统一定义应用名和版本号
    set(PACKAGE_NAME "org.qtproject.SonixBeauty")
    set(VERSION_CODE 1)
    set(VERSION_NAME "1.0.0.0")
    set(APP_NAME "SonixBeauty Studio")
    set(APP_ICON "@drawable/ic_launcher")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/config/Android/android-build"
        QT_ANDROID_PACKAGE_NAME "${PACKAGE_NAME}"
        QT_ANDROID_APP_ICON "${APP_ICON}" # 应用图标
        QT_ANDROID_APP_NAME "${APP_NAME}" # 应用名称
        QT_ANDROID_APP_DESCRIPTION "A beautiful application created with Qt" # 应用描述
        QT_ANDROID_VERSION_CODE ${VERSION_CODE} # 应用版本号
        QT_ANDROID_VERSION_NAME "${VERSION_NAME}" # 版本号名称
        QT_ANDROID_APPLICATION_ARGUMENTS "--appname=${APP_NAME} --version=${VERSION_NAME}" # 启动参数
        QT_ANDROID_ENVIRONMENT_VARIABLES "qt_android_no_exit_call=1" # Android 环境变量
    )
endif()
