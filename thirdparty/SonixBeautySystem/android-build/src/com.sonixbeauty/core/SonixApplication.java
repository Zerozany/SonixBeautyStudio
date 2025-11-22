package com.sonixbeauty.core;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;
import android.util.Log;
import com.sonixbeauty.drive.ActivityControl;
import com.sonixbeauty.utiles.SonixUtiles;

public class SonixApplication extends org.qtproject.qt.android.bindings.QtApplication {

    private ActivityControl m_activityControl = null;

    @Override
    public void onCreate()
    {
        super.onCreate();
        m_activityControl = new ActivityControl();
        registerActivityLifecycleCallbacks(m_activityControl);
        Log.d(SonixUtiles.SonixDebug, "SonixApplication Android onCreate");
    }
}
