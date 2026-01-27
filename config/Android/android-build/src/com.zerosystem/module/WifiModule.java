package com.zerosystem.module;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiNetworkSpecifier;
import android.os.Build;
import android.provider.Settings;
import android.util.Log;
import com.zerosystem.utiles.MessageUtile;
import java.util.List;

public class WifiModule {
    public static final int DISCONNECTED = 0;
    public static final int CONNECTSUCCESS = 1;
    public static final int CONNECTERROR = 2;

    private Activity m_activity;
    private WifiManager m_wifiManager;

    private native void connectSuccess(int state);

    public WifiModule(Activity _activity)
    {
        init(_activity);
    }

    private void init(Activity _activity)
    {
        this.m_activity = _activity;
        m_wifiManager = (WifiManager)m_activity.getApplicationContext().getSystemService(Context.WIFI_SERVICE);
        if (m_wifiManager == null) {
            Log.d(MessageUtile.HandleDebug, "wifiManager init failed");
        }
    }

    // 扫描 Wi-Fi 列表
    public String scanWifiList()
    {
        try {
            if (Build.VERSION.SDK_INT < Build.VERSION_CODES.Q) {
                @SuppressWarnings("deprecation")
                boolean result = m_wifiManager.setWifiEnabled(true);
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
                sb.append("\"").append(result.getWifiSsid().toString()).append(" ").append(result.level).append("\n");
            }
            return sb.toString();
        } catch (Exception e) {
            Log.d(MessageUtile.HandleDebug, "scanAndGetWifiList error: " + e.getMessage());
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

    // 连接 Wi-Fi
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

            ConnectivityManager cm = (ConnectivityManager)m_activity
                                         .getSystemService(Context.CONNECTIVITY_SERVICE);
            if (cm == null) {
                Log.e(MessageUtile.HandleDebug, "ConnectivityManager is null");
                return;
            }

            cm.requestNetwork(request, new ConnectivityManager.NetworkCallback() {
                @Override
                public void onAvailable(Network network)
                {
                    Log.d(MessageUtile.HandleDebug, "Connected to Wi-Fi: " + ssid);
                    cm.bindProcessToNetwork(network);
                    connectSuccess(CONNECTSUCCESS);
                }

                @Override
                public void onUnavailable()
                {
                    Log.d(MessageUtile.HandleDebug, "Failed to connect to Wi-Fi: " + ssid);
                    connectSuccess(CONNECTERROR);
                }

                @Override
                public void onLost(Network network)
                {
                    Log.d(MessageUtile.HandleDebug, "Wi-Fi disconnected: " + ssid);
                    connectSuccess(DISCONNECTED);
                }
            });
            Log.d(MessageUtile.HandleDebug, "Requesting connection to Wi-Fi: " + ssid);
        } catch (Exception e) {
            Log.e(MessageUtile.HandleDebug, "connectWifi error: " + e.getMessage(), e);
        }
    }
}
