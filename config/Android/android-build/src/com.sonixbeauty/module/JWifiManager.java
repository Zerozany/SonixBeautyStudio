package com.sonixbeauty.module;

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
import android.util.Log;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import com.sonixbeauty.utiles.MessageUtile;
import java.util.List;
import org.json.JSONArray;
import org.json.JSONObject;

public final class JWifiManager {

    private static final int LOCATION_PERMISSION_REQUEST_CODE = 1001;
    private Activity m_activity;
    private WifiManager m_wifiManager;

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
                Log.d(MessageUtile.HandleDebug, "startScan failed");
                return "[]";
            }
            List<ScanResult> scanResults = m_wifiManager.getScanResults();
            if (scanResults == null || scanResults.isEmpty()) {
                Log.d(MessageUtile.HandleDebug, "No scan results");
                return "[]";
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
            Log.e(MessageUtile.HandleDebug, "getWifiList error: " + e.getMessage());
            return "[]";
        }
    }

    // 获取当前 Wi-Fi SSID
    @SuppressWarnings({ "deprecation" })
    public String currentWifiName()
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
