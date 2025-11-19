package com.sonixbeauty.activity;

import android.app.Activity;
import android.os.Build; // 用于检查 Android 系统版本
import android.view.View; // 用于访问 View 和其方法
import android.view.Window; // 用于获取窗口（Window）并设置系统 UI 可见性

public class PrivateConfig {
    private static final String TAG = "SonixBeauty";

    public void systemColumnHandle(Activity activity)
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            View decorView = activity.getWindow().getDecorView();
            int uiOptions = View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
            decorView.setSystemUiVisibility(uiOptions);
        }
    }
}
