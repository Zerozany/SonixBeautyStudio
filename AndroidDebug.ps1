# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
# adb.exe 完整路径
$adb = "D:\AndroidEnv\SDK\platform-tools\adb.exe"

& $adb devices

# 设备序列号
$device = "8c1161c0"
# e2feb7f9 8c1161c0

# APK 路径
$apkPath = "F:\DevelopFiles\AndroidFrame\build\AndroidDebug\android-build\SonixBeautyStudio.apk"

# 安装 APK
Write-Host "installing APK..."
& $adb -s $device install -r $apkPath

# 清屏
Clear-Host

# 清除 logcat 日志
Write-Host "clear logcat log..."
& $adb -s $device logcat -c

# 打印指定日志
Write-Host "start print log..."
& $adb -s $device logcat -s "qml:*" "System.out:D" "default:D" "SonixBeauty"
#& $adb -s $device logcat -s "*:V"
