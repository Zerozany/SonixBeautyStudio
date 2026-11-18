# AndroidDebug.ps1

param(
    [string]$d,
    [string]$t,
    [switch]$h,
    [switch]$clean,   # 清理 build 目录
    [switch]$aab      # 新增：打包 AAB（仅 Android）
)

if ($h) {
    Write-Host "Usage: .\buildApplication.ps1 -d <device: p/a> -t <build type: d/r> [-clean] [-aab]"
    exit 0
}

# 默认 build type 为 Debug
if (-not $t) { $t = "d" }
$buildType = if ($t -eq "r") { "Release" } else { "Debug" }

# 获取当前脚本所在的目录
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location "$scriptDir\.."

# 清理 build 目录（可选）
Clear-Host
if (Test-Path "build") {
    Write-Host "🗑️ Found build folder..."
    
    if ($clean) {
        Write-Host "🔥 Removing build folder..."
        Remove-Item -Recurse -Force build
    }
    else {
        Write-Host "⏭️ Skip removing build folder (use -clean to enable)"
    }
}

# 根据 device 构建
switch ($d) {
    "a" {
        $configurePreset = if ($buildType -eq "Debug") { "AndroidDebug" } else { "AndroidRelease" }
        $buildPreset = if ($buildType -eq "Debug") { "AndroidDebugBuild" } else { "AndroidReleaseBuild" }
    }
    "p" {
        $configurePreset = if ($buildType -eq "Debug") { "WindowsDebug" } else { "WindowsRelease" }
        $buildPreset = if ($buildType -eq "Debug") { "WindowsDebugBuild" } else { "WindowsReleaseBuild" }
    }
    Default {
        Write-Host "❌ Unknown device: $d"
        exit 1
    }
}

# AAB 只对 Android 有意义
if ($aab -and $d -ne "a") {
    Write-Host "⚠️ -aab 仅支持 Android (-d a)，已忽略" -ForegroundColor Yellow
    $aab = $false
}

# CMake Configure
Write-Host "=== 🔧 CMake Configure ==="
$proc = Start-Process cmake -ArgumentList "--preset $configurePreset" -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "❌ CMake configure failed!" -ForegroundColor Red
    exit 1
}

# CMake Build
Write-Host "=== 🏗️ CMake Build ==="
$proc = Start-Process cmake -ArgumentList "--build --preset $buildPreset" -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "❌ CMake build failed!" -ForegroundColor Red
    exit 1
}

# AAB 打包（仅 Android 且带 -aab 时）
if ($aab) {
    Write-Host "=== 📦 CMake Build AAB ==="

    $buildDir = "build\$configurePreset"

    $proc = Start-Process cmake `
        -ArgumentList "--build --preset $buildPreset --target SonixBeautyStudio_make_aab" `
        -NoNewWindow -Wait -PassThru

    if ($proc.ExitCode -ne 0) {
        Write-Host "❌ CMake AAB build failed!" -ForegroundColor Red
        exit 1
    }

    $aabPath = Get-ChildItem -Path "$buildDir\android-build" `
        -Filter *.aab -Recurse -ErrorAction SilentlyContinue

    if ($aabPath) {
        Write-Host "✅ AAB 已生成：" -ForegroundColor Green
        $aabPath | ForEach-Object {
            Write-Host "   $($_.FullName)"
        }
    }
    else {
        Write-Host "⚠️ 未在 $buildDir\android-build 找到 .aab 文件" -ForegroundColor Yellow
    }
}

# Install
Write-Host "=== 📦 CMake Install ==="
$proc = Start-Process cmake -ArgumentList "--install $scriptDir\..\build\$configurePreset --config $buildType" -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "❌ CMake install failed!" -ForegroundColor Red
    exit 1
}

Write-Host "✅ Build finished successfully!" -ForegroundColor Green
