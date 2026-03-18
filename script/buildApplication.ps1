# AndroidDebug.ps1

param(
    [string]$d,
    [string]$t,
    [switch]$h,
    [switch]$clean   # ✅ 新增参数
)

if ($h) {
    Write-Host "Usage: .\buildApplication.ps1 -d <device: p/a> -t <build type: d/r> [-clean]"
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
        $configurePreset = if ($buildType -eq "Debug") { "PcDebug" } else { "PcRelease" }
        $buildPreset = if ($buildType -eq "Debug") { "PcDebugBuild" } else { "PcReleaseBuild" }
    }
    Default {
        Write-Host "❌ Unknown device: $d"
        exit 1
    }
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

# Install
Write-Host "=== 📦 CMake Install ==="
$proc = Start-Process cmake -ArgumentList "--install $scriptDir\..\build\$configurePreset --config $buildType" -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "❌ CMake install failed!" -ForegroundColor Red
    exit 1
}

Write-Host "✅ Build finished successfully!" -ForegroundColor Green
