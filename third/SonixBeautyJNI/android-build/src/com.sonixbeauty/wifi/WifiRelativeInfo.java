package com.sonixbeauty.wifi;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiNetworkSpecifier;
import android.util.Log;
import androidx.core.app.ActivityCompat;
import java.util.ArrayList;
import java.util.List;

public class WifiRelativeInfo {
    public static final int DISCONNECTED = 0;
    public static final int CONNECTSUCCESS = 1;
    public static final int CONNECTERROR = 2;

    private Activity m_activity;
    private WifiManager m_wifiManager;
    private final int REQUEST_LOCATION_PERMISSION = 1001;
    private static final String TAG = "SonixBeauty"; // 全局统一 TAG

    // 声明 native 方法
    private native void connectSuccess(int state);

    public WifiRelativeInfo(Activity _activity)
    {
        init(_activity);
        requestPermission();
    }

    private void init(Activity _activity)
    {
        this.m_activity = _activity;
        m_wifiManager = (WifiManager)m_activity.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        if (m_wifiManager == null) {
            Log.d(TAG, "wifiManager init failed");
            return;
        }
    }

    private void requestPermission()
    {
        // 要请求的权限数组
        String[] permissions = {
            Manifest.permission.ACCESS_FINE_LOCATION,
            Manifest.permission.CHANGE_WIFI_STATE
        };
        // 遍历检查是否有未授权的权限
        List<String> permissionNeeded = new ArrayList<>();
        for (String permission : permissions) {
            if (ActivityCompat.checkSelfPermission(m_activity, permission) != PackageManager.PERMISSION_GRANTED) {
                permissionNeeded.add(permission);
            }
        }
        // 如果有未授权的权限，统一请求
        if (!permissionNeeded.isEmpty()) {
            ActivityCompat.requestPermissions(m_activity, permissionNeeded.toArray(new String[0]), REQUEST_LOCATION_PERMISSION);
            Log.d(TAG, "Requesting location and wifi permissions: " + permissionNeeded);
        }
    }

    public String scanWifiList()
    {
        try {
            if (!m_wifiManager.isWifiEnabled()) {
                m_wifiManager.setWifiEnabled(true);
            }
            @SuppressWarnings("deprecation")
            boolean success = m_wifiManager.startScan();
            if (!success) {
                return "NULL";
            }
            List<ScanResult> scanResults = m_wifiManager.getScanResults();
            if (scanResults == null || scanResults.isEmpty()) {
                return "NULL";
            }
            StringBuilder sb = new StringBuilder();
            for (ScanResult result : scanResults) {
                sb.append(result.SSID).append(" ").append(result.level).append(",");
            }
            return sb.toString();
        } catch (Exception e) {
            Log.d(TAG, "scanAndGetWifiList error: " + e.getMessage());
            return "NULL";
        }
    }

    // 获取当前 Wi-Fi SSID
    public String getCurrentWifiSSID()
    {
        try {
            @SuppressWarnings("deprecation")
            WifiInfo wifiInfo = m_wifiManager.getConnectionInfo();
            if (wifiInfo == null) {
                return "NULL";
            }
            String ssid = wifiInfo.getSSID();
            if (ssid.startsWith("\"") && ssid.endsWith("\"")) {
                ssid = ssid.substring(1, ssid.length() - 1);
            }
            return ssid;
        } catch (Exception e) {
            return "NULL";
        }
    }

    public void connectWifi(String ssid, String password)
    {
        try {
            WifiNetworkSpecifier specifier = new WifiNetworkSpecifier.Builder()
                                                 .setSsid(ssid)
                                                 .setWpa2Passphrase(password)
                                                 .build();

            NetworkRequest request = new NetworkRequest.Builder()
                                         .addTransportType(NetworkCapabilities.TRANSPORT_WIFI)
                                         .setNetworkSpecifier(specifier)
                                         .build();

            ConnectivityManager cm = (ConnectivityManager)m_activity.getSystemService(Context.CONNECTIVITY_SERVICE);
            if (cm == null) {
                Log.e(TAG, "ConnectivityManager is null");
                return;
            }
            cm.requestNetwork(request, new ConnectivityManager.NetworkCallback() {
                @Override
                public void onAvailable(Network network)
                {
                    // 连接成功
                    Log.d(TAG, "Connected to Wi-Fi: " + ssid);
                    cm.bindProcessToNetwork(network); // 可选，将 app 网络绑定到指定 Wi-Fi
                    connectSuccess(CONNECTSUCCESS);
                }
                @Override
                public void onUnavailable()
                {
                    Log.d(TAG, "Failed to connect to Wi-Fi: " + ssid);
                    connectSuccess(CONNECTERROR);
                }
                @Override
                public void onLost(Network network)
                {
                    Log.d(TAG, "Wi-Fi disconnected: " + ssid);
                    connectSuccess(DISCONNECTED);
                }
            });
            Log.d(TAG, "Requesting connection to Wi-Fi: " + ssid);
        } catch (Exception e) {
            Log.e(TAG, "connectWifi error: " + e.getMessage(), e);
        }
    }
}
