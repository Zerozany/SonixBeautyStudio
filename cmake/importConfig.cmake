target_compile_features(${PROJECT_NAME}
    PRIVATE
    cxx_std_23
)

if(MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        "/utf-8"
        "/FS"
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:/Od>"
        "$<$<CONFIG:Release>:/Ox>"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        "-fdiagnostics-color=always" # 彩色输出诊断信息
        "-Wall" # 开启大部分警告
        "-Wextra" # 更多警告
        "$<$<CONFIG:Debug>:-O0>" # Debug 禁用优化
        "$<$<CONFIG:Release>:-O3>" # Release 最大优化
    )
endif()

if(WIN32)
    # 检查目标类型，只有可执行文件才使用 windeployqt
    get_target_property(TARGET_TYPE ${PROJECT_NAME} TYPE)

    if(TARGET_TYPE STREQUAL "EXECUTABLE")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "$ENV{Qt6_BIN_DIR}/windeployqt.exe"
                $<$<CONFIG:Debug>:--debug>
                $<$<CONFIG:Release>:--release>
                --qmldir "${CMAKE_BINARY_DIR}/qmlimports"
                $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Deploying Qt dependencies for ${PROJECT_NAME}"
        )
    else()
        message(STATUS "skip windeployqt: ${PROJECT_NAME} It is not an executable file")
    endif()
elseif(ANDROID)
    # # Android Studio 实时查看Debug、QML打印
    # 连接模拟器
    # .\adb.exe logcat -c ; .\adb.exe logcat -s "qml:*" "System.out:I" "default:D"
    # 连接真机（d933be15 为真实设备序号）
    # .\adb.exe devices
    # .\adb.exe -s d933be15 logcat -c;.\adb.exe -s d933be15 logcat -s "qml:*" "System.out:I" "default:D"
    # 真机自动安装apk（F:\DevelopFiles\AndroidFrame\build\AndroidDebug\android-build\SonixBeautyStudio.apk为apk所在路径）
    # .\adb.exe -s d933be15 install -r F:\DevelopFiles\AndroidFrame\build\AndroidDebug\android-build\SonixBeautyStudio.apk
    # powershell获取脚本权限：'Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass'

    # 统一定义应用名和版本号
    set(PACKAGE_NAME "org.qtproject.SonixBeauty")
    set(APP_NAME "SonixBeauty Studio")
    set(VERSION_NAME "1.0.0.0")

    set_target_properties(${PROJECT_NAME} PROPERTIES
        QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/third/SonixBeautyJNI/android-build"
        QT_ANDROID_PACKAGE_NAME "${PACKAGE_NAME}"
        QT_ANDROID_APP_ICON "@drawable/ic_launcher"
        QT_ANDROID_APP_NAME "${APP_NAME}" # 应用名称
        QT_ANDROID_APP_DESCRIPTION "A beautiful application created with Qt" # 应用描述
        QT_ANDROID_VERSION_CODE 1 # 应用版本号
        QT_ANDROID_VERSION_NAME "${VERSION_NAME}" # 版本号名称
        QT_ANDROID_APPLICATION_ARGUMENTS "--appname=${APP_NAME} --version=${VERSION_NAME}" # 启动参数
        QT_ANDROID_ENVIRONMENT_VARIABLES "qt_android_no_exit_call=1" # Android 环境变量
    )
endif()
