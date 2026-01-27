package com.zerosystem.core;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import com.zerosystem.system.SystemConfig;
import com.zerosystem.utiles.MessageUtile;

public class MainActivity extends org.qtproject.qt.android.bindings.QtActivity {

    private SystemConfig m_systemConfig = null;

    private static native void QActivityVisibileChanged(boolean _activitySwitch);

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
        m_systemConfig = new SystemConfig();
        m_systemConfig.systemColumnHandle(this);
    }

    @Override
    public void onWindowFocusChanged(boolean _hasFocus)
    {
        super.onWindowFocusChanged(_hasFocus);
        if (_hasFocus) {
            QActivityVisibileChanged(true);
        } else {
            QActivityVisibileChanged(false);
        }
        Log.d(MessageUtile.HandleDebug, "QActivityVisibileChanged: " + _hasFocus);
    }
}
