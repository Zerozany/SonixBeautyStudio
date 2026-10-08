# Qt SonixBeauty
- `git submodule update --init --recursive`

- [x] [Windows、Android下Wifi设备连接](#Wifi设备连接)  

## Wifi以及Tcp连接

### Wifi相关接口

- 模块类获取实例
```cpp
DevicesManager::create();
```
> QML获取方式: DevicesManager即可

- 刷新Wifi(`WLAN`)列表
```cpp
Q_INVOKABLE void refreshDevicesList();
```
> Windows系统下无延迟实时刷新、Android系统下由于谷歌平台的限制多次刷新之后需间隔30s~2分钟后可再次刷新

- 获取Wifi(`WLAN`)列表
```cpp
QVariantList devicesList()
```
> QML获取方式: DevicesManager.devicesList

- 获取当前所连接Wifi(`WLAN`)名称
```cpp
Q_INVOKABLE QString currentWifiName();
```
- 获取当前所连接Wifi(`WLAN`)信号强度
```cpp
Q_INVOKABLE QString currentWifiSignalQuality();
```
- 连接Wifi(`WLAN`)
```cpp
Q_INVOKABLE void connectToWifi(const QString& _ssid, const QString& _password);
```
> 1. _ssid: 所需连接的Wifi(`WLAN`)名称
> 2. _password: 所需连接的Wifi(`WLAN`)密码

- 断开当前所连接的Wifi(`WLAN`)
```cpp
Q_INVOKABLE void disconnectWifi();
```

### Wifi相关触发Qt信号

- Wifi(`WLAN`)连接成功
```cpp
void wifiConnectSuccessful();
```

- Wifi(`WLAN`)连接失败
```cpp
void wifiConnectFailed();
```  

- Wifi(`WLAN`)连接断开
```cpp
void wifiLost();
```

