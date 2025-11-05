package com.sonixbeauty.activity;

import android.os.Build; // 用于检查 Android 系统版本
import android.os.Bundle;
import android.util.Log;
import android.view.View; // 用于访问 View 和其方法
import android.view.Window; // 用于获取窗口（Window）并设置系统 UI 可见性

public class AppActivity extends org.qtproject.qt.android.bindings.QtActivity {

    private static final String TAG = "SonixBeauty";
    public static native void nativeNotifyCreate();
    public static native void nativeNotifyStart();
    public static native void nativeNotifyStop();
    public static native void nativeNotifyRestart();

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
            View decorView = getWindow().getDecorView();
            int uiOptions = View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;
            decorView.setSystemUiVisibility(uiOptions);
        }
    }

    @Override
    public void onStart()
    {
        nativeNotifyStart();
        super.onStart();
    }

    @Override
    public void onStop()
    {
        super.onStop();
        nativeNotifyStop();
    }

    @Override
    public void onResume()
    {
        super.onResume();
    }

    @Override
    public void onRestart()
    {
        nativeNotifyRestart();
        super.onRestart();
    }

    @Override
    public void onPause()
    {
        super.onPause();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }
}
