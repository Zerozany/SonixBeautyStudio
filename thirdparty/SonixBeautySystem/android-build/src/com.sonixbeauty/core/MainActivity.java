package com.sonixbeauty.core;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import com.sonixbeauty.system.SystemConfig;
import com.sonixbeauty.utiles.MessageUtile;

public class MainActivity extends org.qtproject.qt.android.bindings.QtActivity {

    private SystemConfig m_systemConfig = null;

    private static native void NotifyCreate();
    private static native void NotifyRestart();
    private static native void NotifyPause();
    private static native void NotifyDestroy();

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
        m_systemConfig = new SystemConfig();
    }

    @Override
    public void onWindowFocusChanged(boolean _hasFocus)
    {
        super.onWindowFocusChanged(_hasFocus);
        if (_hasFocus) {
            m_systemConfig.systemColumnHandle(this);
        } else {
        }
        Log.d(MessageUtile.HandleDebug, "[MainActivity.java] hasWindowFocus: " + _hasFocus);
    }

    @Override
    public void onRestart()
    {
        NotifyRestart();
        super.onRestart();
    }

    @Override
    public void onPause()
    {
        NotifyPause();
        super.onPause();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }
}
