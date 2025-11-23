package com.sonixbeauty.core;

import android.app.Application;
import android.os.Bundle;
import android.util.Log;
import com.sonixbeauty.drive.ActivityControl;
import com.sonixbeauty.utiles.JNIUtiles;

public class JNIApplication extends org.qtproject.qt.android.bindings.QtApplication {

    private ActivityControl m_activityControl = null;

    @Override
    public void onCreate()
    {
        super.onCreate();
        m_activityControl = new ActivityControl();
        registerActivityLifecycleCallbacks(m_activityControl);
        Log.d(JNIUtiles.HandleDebug, "[JNIApplication.java]:JNIApplication Android onCreate");
    }
}
