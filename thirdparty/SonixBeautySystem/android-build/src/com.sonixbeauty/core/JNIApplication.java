package com.sonixbeauty.core;

import android.app.Application;
import android.os.Bundle;
import android.util.Log;
import com.sonixbeauty.utiles.MessageUtile;

public class JNIApplication extends org.qtproject.qt.android.bindings.QtApplication {

    @Override
    public void onCreate()
    {
        super.onCreate();
        Log.d(MessageUtile.HandleDebug, "[JNIApplication.java]:JNIApplication for Android onCreate");
    }
}
