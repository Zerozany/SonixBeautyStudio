package com.sonixbeauty.activity;

import android.os.Bundle;
import android.util.Log;

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
        // nativeNotifyResume();
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
        // nativeNotifyPause();
    }

    @Override
    public void onDestroy()
    {
        // nativeNotifyDestroy();
        super.onDestroy();
    }
}
