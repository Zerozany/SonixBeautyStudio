package com.zerosystem.module;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.util.Log;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import com.zerosystem.utiles.MessageUtile;
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
    public String getWifiList()
    {
        try {
            boolean success = m_wifiManager.startScan();
            if (!success) {
                Log.d(MessageUtile.HandleDebug, "startScan failed");
                return "NULL";
            }
            List<ScanResult> scanResults = m_wifiManager.getScanResults();
            if (scanResults == null || scanResults.isEmpty()) {
                Log.d(MessageUtile.HandleDebug, "No scan results");
                return "NULL";
            }
            StringBuilder wifiList = new StringBuilder();
            for (ScanResult result : scanResults) {
                wifiList.append(result.SSID).append("  ").append(result.level).append("\n");
            }
            return wifiList.toString();
        } catch (Exception e) {
            Log.e(MessageUtile.HandleDebug, "getWifiList error: " + e.getMessage());
            return "NULL";
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
}
