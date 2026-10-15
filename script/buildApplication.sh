#!/bin/bash

# 解析参数
while getopts "d:t:h" opt; do
    case $opt in
        d) device=$OPTARG ;;
        t) type=$OPTARG ;;
        h) echo "Usage: $0 -d <device: p/a> -t <build type: d/r>"; exit 0 ;;
        ?) echo "Unknown params"; exit 1 ;;
    esac
done

# 默认 build type 为 Debug
if [ -z "$type" ]; then
    type="d"
fi

if [ "$type" = "r" ]; then
    buildType="Release"
else
    buildType="Debug"
fi

# 获取当前脚本所在的目录
scriptDir=$(dirname "$0")
# 切换到脚本所在目录的上一级目录
cd "$scriptDir/.."

clear
rm -rf build

# 根据 device 构建
if [ "$device" = "a" ]; then
    # Android 构建
    if [ "$buildType" = "Debug" ]; then
        configurePreset="AndroidDebug"
        buildPreset="AndroidDebugBuild"
    else
        configurePreset="AndroidRelease"
        buildPreset="AndroidReleaseBuild"
    fi

elif [ "$device" = "p" ]; then
    # PC 构建
    if [ "$buildType" = "Debug" ]; then
        configurePreset="PcDebug"
        buildPreset="PcDebugBuild"
    else
        configurePreset="PcRelease"
        buildPreset="PcReleaseBuild"
    fi

else
    echo "❌ Unknown device: $device"
    exit 1
fi

# 构建编译
cmake --preset $configurePreset 
if [ $? -eq 0 ]; then
    cmake --build --preset $buildPreset 
else
    echo "❌ CMake configuration failed!"
    exit 1
fi
