# AndroidDebug.ps1

param(
    [string]$d,
    [string]$t,
    [switch]$h
)

if ($h) {
    Write-Host "Usage: .\AndroidDebug.ps1 -d <device: p/a> -t <build type: d/r>"
    exit 0
}

# 默认 build type 为 Debug
if (-not $t) { $t = "d" }
$buildType = if ($t -eq "r") { "Release" } else { "Debug" }

# 清理 build 目录
Clear-Host
if (Test-Path "build") {
    Write-Host "🗑️ Removing old build folder..."
    # Remove-Item -Recurse -Force build
}

# 根据 device 构建
switch ($d) {
    "a" {
        # Android 构建
        $configurePreset = if ($buildType -eq "Debug") { "AndroidDebug" } else { "AndroidRelease" }
        $buildPreset = if ($buildType -eq "Debug") { "AndroidDebugBuild" } else { "AndroidReleaseBuild" }
    }
    "p" {
        # PC 构建
        $configurePreset = if ($buildType -eq "Debug") { "PcDebug" } else { "PcRelease" }
        $buildPreset = if ($buildType -eq "Debug") { "PcDebugBuild" } else { "PcReleaseBuild" }
    }
    Default {
        Write-Host "❌ Unknown device: $d"
        exit 1
    }
}

Write-Host "📌 Device: $d"
Write-Host "📌 BuildType: $buildType"
Write-Host "📌 ConfigurePreset: $configurePreset"
Write-Host "📌 BuildPreset: $buildPreset"

# 执行 CMake 配置
Write-Host "=== 🔧 CMake Configure ==="
$proc = Start-Process cmake -ArgumentList "--preset $configurePreset" -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "❌ CMake configure failed!" -ForegroundColor Red
    exit 1
}

# 执行 CMake 构建
Write-Host "=== 🏗️ CMake Build ==="
$proc = Start-Process cmake -ArgumentList "--build --preset $buildPreset" -NoNewWindow -Wait -PassThru
if ($proc.ExitCode -ne 0) {
    Write-Host "❌ CMake build failed!" -ForegroundColor Red
    exit 1
}

Write-Host "✅ Build finished successfully!" -ForegroundColor Green
