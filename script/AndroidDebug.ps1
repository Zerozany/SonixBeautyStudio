# Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass

param(
    [ValidateSet("d", "r")]
    [string]$t = "d"
)

# adb.exe path
$adb = "D:\AndroidEnv\SDK\platform-tools\adb.exe"

# device serial
$device = "e2feb7f9"
# e2feb7f9 8c1161c0 d933be15

# APK paths
$apkPathDebug   = "$(Resolve-Path "$PSScriptRoot\..")\build\AndroidDebug\android-build\build\outputs\apk\debug\android-build-debug.apk"
$apkPathRelease = "$(Resolve-Path "$PSScriptRoot\..")\build\AndroidRelease\android-build\build\outputs\apk\release\android-build-release-signed.apk"

# choose APK
switch ($t) {
    "d" {
        $apkPath = $apkPathDebug
        Write-Host "Mode: DEBUG"
    }
    "r" {
        $apkPath = $apkPathRelease
        Write-Host "Mode: RELEASE"
    }
}

# package name
$packageName = "org.qtproject.SonixBeauty"

# check apk exists
if (!(Test-Path $apkPath)) {
    Write-Host "ERROR: APK not found:"
    Write-Host $apkPath
    exit 1
}

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
        exit 1
    }
}

Write-Host "App PID = $appPID"

# 5. print logs
Write-Host "Start printing logs..."
& $adb -s $device logcat --pid=$appPID "*:V"
# 或你原来的过滤
# & $adb -s $device logcat -s "qml:*" "System.out:D" "default:D" "HandleDebug"
