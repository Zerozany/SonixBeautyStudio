package com.sonixbeauty.activity;

import android.os.Bundle;
import android.util.Log;

public class AppActivity extends org.qtproject.qt.android.bindings.QtActivity {

    private static final String TAG = "SonixBeauty";
    private static native void nativeNotifyCreate();
    private static native void nativeNotifyStart();
    private static native void nativeNotifyStop();
    private static native void nativeNotifyRestart();
    private static native void nativeNotifyPause();

    private PrivateConfig m_privateConfig;

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
        m_privateConfig = new PrivateConfig();
        m_privateConfig.systemColumnHandle(this);
    }

    @Override
    public void onStart()
    {
        super.onStart();
    }

    @Override
    public void onStop()
    {
        super.onStop();
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
        nativeNotifyPause();
        super.onPause();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }
}
