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
import org.json.JSONObject;

public final class JWifiManager {

    private static final int LOCATION_PERMISSION_REQUEST_CODE = 1001;
    private Activity m_activity;
    private WifiManager m_wifiManager;
    private ConnectivityManager m_connectivityManager;
    private java.util.List<ConnectivityManager.NetworkCallback> m_callbacks = new java.util.ArrayList<>();

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
                Log.d("HandleDebug", "startScan failed");
                return "";
            }
            List<ScanResult> scanResults = m_wifiManager.getScanResults();
            if (scanResults == null || scanResults.isEmpty()) {
                Log.d("HandleDebug", "No scan results");
                return "";
            }
            JSONArray array = new JSONArray();
            for (ScanResult result : scanResults) {
                JSONObject obj = new JSONObject();
                obj.put("ssid", result.SSID);
                obj.put("level", WifiManager.calculateSignalLevel(result.level, 101));
                array.put(obj);
            }
            return array.toString();
        } catch (Exception e) {
            Log.e("HandleDebug", "getWifiList error: " + e.getMessage());
            return "";
        }
    }

    // 获取当前 Wi-Fi SSID
    public String currentWifiName()
    {
        try {
            if (m_connectivityManager == null) {
                return "";
            }
            Network network = m_connectivityManager.getActiveNetwork();
            if (network == null) {
                return "";
            }
            NetworkCapabilities caps = m_connectivityManager.getNetworkCapabilities(network);
            if (caps == null || !caps.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                return ""; // 当前不是 Wi-Fi，直接返回空
            }
            WifiInfo wifiInfo = m_wifiManager.getConnectionInfo();
            if (wifiInfo == null) {
                return "";
            }
            String ssid = wifiInfo.getSSID();
            if (ssid == null) {
                return "";
            }
            // 去掉引号
            if (ssid.startsWith("\"") && ssid.endsWith("\"") && ssid.length() >= 2) {
                ssid = ssid.substring(1, ssid.length() - 1);
            }
            // 过滤掉无效值
            if (ssid.equals("<unknown ssid>") || ssid.equals("0x")) {
                return "";
            }
            return ssid;
        } catch (Exception e) {
            return "";
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
                Log.d("HandleDebug", "Connected to " + ssid);
            }
            @Override
            public void onUnavailable()
            {
                Log.d("HandleDebug", "Failed to connect to " + ssid);
            }
            @Override
            public void onLost(Network network)
            {
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
        Log.d("HandleDebug", "All callbacks unregistered");
    }
}
