package com.sonixbeauty.module;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiNetworkSpecifier;
import android.util.Log;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import java.util.List;
import org.json.JSONArray;

public final class JWifiManager {

    private static final int LOCATION_PERMISSION_REQUEST_CODE = 1001;
    private Activity m_activity;
    private WifiManager m_wifiManager;
    private ConnectivityManager m_connectivityManager;
    private java.util.List<ConnectivityManager.NetworkCallback> m_callbacks = new java.util.ArrayList<>();

    private static native void QWifiConnectedSuccessful();
    private static native void QWifiConnectedFailed();
    private static native void QWifiLost();

    public JWifiManager(Activity _activity)
    {
        init(_activity);
    }

    private void init(Activity _activity)
    {
        this.m_activity = _activity;
        m_wifiManager = (WifiManager)m_activity.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        if (m_wifiManager == null) {
            return;
        }
        m_connectivityManager = (ConnectivityManager)m_activity.getSystemService(Context.CONNECTIVITY_SERVICE);

        if (ContextCompat.checkSelfPermission(m_activity, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(m_activity, new String[] { Manifest.permission.ACCESS_FINE_LOCATION }, LOCATION_PERMISSION_REQUEST_CODE);
        }
    }

    // 扫描 Wi-Fi 列表
    @SuppressWarnings({ "deprecation" })
    public String getWifiList()
    {
        try {
            boolean success = m_wifiManager.startScan();
            if (!success) {
                Log.e("HandleDebug", "startScan frequency too high");
                // return "";
            }
            List<ScanResult> scanResults = m_wifiManager.getScanResults();
            if (scanResults == null || scanResults.isEmpty()) {
                Log.e("HandleDebug", "No scan results");
                return "";
            }
            JSONArray array = new JSONArray();
            for (ScanResult result : scanResults) {
                JSONArray pair = new JSONArray();
                pair.put(result.SSID);
                pair.put(WifiManager.calculateSignalLevel(result.level, 101));
                array.put(pair);
            }
            return array.toString();
        } catch (Exception e) {
            Log.e("HandleDebug", "getWifiList error: " + e.getMessage());
            return "";
        }
    }

    // 获取当前 Wi-Fi SSID
    @SuppressWarnings({ "deprecation" })
    public String currentWifiName()
    {
        try {
            if (m_wifiManager == null) {
                Log.e("HandleDebug", "WifiManager is null");
                return "";
            }
            WifiInfo wifiInfo = m_wifiManager.getConnectionInfo();
            if (wifiInfo == null) {
                Log.e("HandleDebug", "WifiInfo is null");
                return "";
            }
            String ssid = wifiInfo.getSSID();
            if (ssid == null || ssid.isEmpty()) {
                Log.e("HandleDebug", "SSID is null or empty");
                return "";
            }
            // Android 未连接 Wi-Fi
            if ("<unknown ssid>".equals(ssid) || "0x".equals(ssid)) {
                Log.e("HandleDebug", "Unknown SSID");
                return "";
            }
            // 去掉 Android 返回的双引号
            if (ssid.startsWith("\"") && ssid.endsWith("\"") && ssid.length() >= 2) {
                ssid = ssid.substring(1, ssid.length() - 1);
            }
            return ssid;
        } catch (Exception e) {
            Log.e("HandleDebug", "currentWifiName exception", e);
            return "";
        }
    }

    // 获取当前 Wi-Fi 信号强度，返回 0~100
    @SuppressWarnings({ "deprecation" })
    public int currentWifiSignalQuality()
    {
        try {
            if (m_wifiManager == null) {
                Log.e("HandleDebug", "WifiManager is null");
                return 0;
            }
            WifiInfo wifiInfo = m_wifiManager.getConnectionInfo();
            if (wifiInfo == null) {
                Log.e("HandleDebug", "WifiInfo is null");
                return 0;
            }
            int rssi = wifiInfo.getRssi();
            if (rssi == -127) {
                Log.e("HandleDebug", "Invalid RSSI: " + rssi);
                return 0;
            }
            return WifiManager.calculateSignalLevel(rssi, 101);
        } catch (Exception e) {
            Log.e("HandleDebug", "currentWifiSignalQuality error: " + e.getMessage(), e);
            return 0;
        }
    }

    public void connectToWifi(String ssid, String password)
    {
        WifiNetworkSpecifier specifier = new WifiNetworkSpecifier.Builder().setSsid(ssid).setWpa2Passphrase(password).build();
        NetworkRequest request = new NetworkRequest.Builder().addTransportType(android.net.NetworkCapabilities.TRANSPORT_WIFI).setNetworkSpecifier(specifier).build();
        ConnectivityManager.NetworkCallback cb = new ConnectivityManager.NetworkCallback() {
            @Override
            public void onAvailable(Network network)
            {
                m_connectivityManager.bindProcessToNetwork(network);
                JWifiManager.QWifiConnectedSuccessful();
                Log.d("HandleDebug", "Connected to " + ssid);
            }
            @Override
            public void onUnavailable()
            {
                JWifiManager.QWifiConnectedFailed();
                Log.d("HandleDebug", "Failed to connect to " + ssid);
            }
            @Override
            public void onLost(Network network)
            {
                JWifiManager.QWifiLost();
                Log.d("HandleDebug", "Lost connection to " + ssid);
            }
        };
        m_callbacks.add(cb);
        m_connectivityManager.requestNetwork(request, cb);
    }

    // 新增：断开 Wi-Fi 连接的方法
    public void disconnectWifi()
    {
        for (ConnectivityManager.NetworkCallback cb : m_callbacks) {
            try {
                m_connectivityManager.unregisterNetworkCallback(cb);
            } catch (Exception e) {
                Log.e("HandleDebug", "unregister error: " + e.getMessage());
            }
        }
        m_callbacks.clear();
        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
            m_connectivityManager.bindProcessToNetwork(null);
        }
        Log.d("HandleDebug", "disconnectWifi ok");
    }
}
