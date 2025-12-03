# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass

# adb.exe path
$adb = "D:\AndroidEnv\SDK\platform-tools\adb.exe"

# device serial
$device = "e2feb7f9"
# e2feb7f9 8c1161c0 d933be15

# APK path
$apkPath = "F:\DevelopFiles\AndroidFrame\build\AndroidDebug\android-build\SonixBeautyStudio.apk"

# package name
$packageName = "org.qtproject.SonixBeauty"

# 1. check devices
Write-Host "Checking connected devices..."
& $adb devices

# 2. install APK
Write-Host "Installing APK..."
& $adb -s $device install -r $apkPath

# 3. clear logcat
Clear-Host
Write-Host "Clearing logcat logs..."
& $adb -s $device logcat -c

# 4. get app PID
Write-Host "Getting app PID..."
$appPID = (& $adb -s $device shell pidof $packageName) -replace '\r','' -replace '\n',''

if ([string]::IsNullOrWhiteSpace($appPID)) {
    Write-Host "App not running, launching..."
    & $adb -s $device shell monkey -p $packageName -c android.intent.category.LAUNCHER 1

    Start-Sleep -Seconds 2

    $appPID = (& $adb -s $device shell pidof $packageName) -replace '\r','' -replace '\n',''

    if ([string]::IsNullOrWhiteSpace($appPID)) {
        Write-Host "ERROR: Failed to get PID for $packageName"
        exit
    }
}

Write-Host "App PID = $appPID"

# 5. print all logs for this app
Write-Host "Start printing ALL logs for this app..."
# & $adb -s $device logcat --pid=$appPID "*:V"
& $adb -s $device logcat -s "qml:*" "System.out:D" "default:D" "HandleDebug"
