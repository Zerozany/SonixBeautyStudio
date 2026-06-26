package com.sonixbeauty.core;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
// import android.util.Log;

public class MainActivity extends org.qtproject.qt.android.bindings.QtActivity {

    private static native void QActivityVisibileChanged(boolean _activitySwitch);

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
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
    }
}
