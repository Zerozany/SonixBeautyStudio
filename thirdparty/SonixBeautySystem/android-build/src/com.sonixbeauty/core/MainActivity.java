package com.sonixbeauty.core;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import com.sonixbeauty.drive.SystemControl;
import com.sonixbeauty.utiles.JNIUtiles;

public class MainActivity extends org.qtproject.qt.android.bindings.QtActivity {

    private SystemControl m_systemControl = null;

    private static native void NotifyCreate();
    private static native void NotifyRestart();
    private static native void NotifyPause();
    private static native void NotifyDestroy();

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
        m_systemControl = new SystemControl();
        // NotifyCreate();
    }

    @Override
    public void onWindowFocusChanged(boolean _hasFocus)
    {
        super.onWindowFocusChanged(_hasFocus);
        if (_hasFocus) {
            m_systemControl.systemColumnHandle(this);
            NotifyRestart();
        } else {
            NotifyPause();
        }
        Log.d(JNIUtiles.HandleDebug, "hasWindowFocus: " + _hasFocus);
    }

    @Override
    public void onRestart()
    {
        // NotifyRestart();
        super.onRestart();
    }

    @Override
    public void onPause()
    {
        // NotifyPause();
        super.onPause();
    }

    @Override
    public void onDestroy()
    {
        // NotifyDestroy();
        super.onDestroy();
    }
}
