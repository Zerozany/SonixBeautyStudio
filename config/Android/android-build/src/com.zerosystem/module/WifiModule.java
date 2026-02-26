package com.zerosystem.module;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkRequest;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiNetworkSpecifier;
import android.os.Build;
import android.util.Log;
import androidx.annotation.RequiresApi;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import com.zerosystem.utiles.MessageUtile;
import java.util.HashMap;
import java.util.List;

public class WifiModule {

    private static final int LOCATION_PERMISSION_REQUEST_CODE = 1001;
    private Activity m_activity;
    private WifiManager m_wifiManager;

    public WifiModule(Activity _activity)
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
        if (ContextCompat.checkSelfPermission(m_activity, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(m_activity, new String[] { Manifest.permission.ACCESS_FINE_LOCATION }, LOCATION_PERMISSION_REQUEST_CODE);
        }
    }

    // 扫描 Wi-Fi 列表
    public HashMap<String, Integer> getWifiMap()
    {
        HashMap<String, Integer> wifiMap = new HashMap<>();
        try {
            boolean success = m_wifiManager.startScan();
            if (!success) {
                return wifiMap;
            }
            List<ScanResult> scanResults = m_wifiManager.getScanResults();
            if (scanResults == null || scanResults.isEmpty()) {
                return wifiMap;
            }
            for (ScanResult result : scanResults) {
                wifiMap.put(result.SSID, WifiManager.calculateSignalLevel(result.level, 101));
            }
            return wifiMap;
        } catch (Exception e) {
            return wifiMap;
        }
    }

    // 获取当前 Wi-Fi SSID
    public String getCurrentWifi()
    {
        try {
            WifiInfo wifiInfo = m_wifiManager.getConnectionInfo();
            if (wifiInfo == null) {
                return "NULL";
            }
            String ssid = wifiInfo.getSSID();
            if (ssid != null && ssid.startsWith("\"") && ssid.endsWith("\"")) {
                ssid = ssid.substring(1, ssid.length() - 1);
            }
            return ssid;
        } catch (Exception e) {
            return "NULL";
        }
    }

    public void connectToWifi(String ssid, String password)
    {
        WifiNetworkSpecifier specifier = new WifiNetworkSpecifier.Builder().setSsid(ssid).setWpa2Passphrase(password).build();
        NetworkRequest request = new NetworkRequest.Builder().addTransportType(android.net.NetworkCapabilities.TRANSPORT_WIFI).setNetworkSpecifier(specifier).build();
        ConnectivityManager cm = (ConnectivityManager)m_activity.getSystemService(Context.CONNECTIVITY_SERVICE);
        ConnectivityManager.NetworkCallback networkCallback = new ConnectivityManager.NetworkCallback() {
            @Override
            public void onAvailable(Network network)
            {
                Log.d(MessageUtile.HandleDebug, "Connected to " + ssid);
                cm.bindProcessToNetwork(network);
            }
            @Override
            public void onUnavailable()
            {
                Log.d(MessageUtile.HandleDebug, "Failed to connect to " + ssid);
            }
        };
        cm.requestNetwork(request, networkCallback);
    }
}
