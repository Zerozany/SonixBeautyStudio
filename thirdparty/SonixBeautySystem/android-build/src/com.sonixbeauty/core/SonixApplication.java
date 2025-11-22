package com.sonixbeauty.core;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;
import android.util.Log;

public class SonixApplication extends org.qtproject.qt.android.bindings.QtApplication {

    private static final String TAG = "SonixBeauty";
    private static native void NotifyRestart();
    private static native void NotifyPause();

    private int activityReferences = 0;
    private boolean isActivityChangingConfigurations = false;

    @Override
    public void onCreate()
    {
        super.onCreate();
        Log.d(TAG, "SonixApplication onCreate");

        // 调用独立方法注册前后台监听
        registerAppLifecycleCallbacks();
    }

    // 独立方法：前后台监听逻辑
    private void registerAppLifecycleCallbacks()
    {
        registerActivityLifecycleCallbacks(new ActivityLifecycleCallbacks() {
            @Override
            public void onActivityStarted(Activity activity)
            {
                if (++activityReferences == 1 && !isActivityChangingConfigurations) {
                    Log.d(TAG, "App enters foreground");
                    NotifyRestart(); // 可以回调 Qt 层
                }
            }

            @Override
            public void onActivityStopped(Activity activity)
            {
                isActivityChangingConfigurations = activity.isChangingConfigurations();
                if (--activityReferences == 0 && !isActivityChangingConfigurations) {
                    Log.d(TAG, "App enters background");
                    NotifyPause(); // 可以回调 Qt 层
                }
            }

            @Override
            public void onActivityCreated(Activity a, Bundle b) { }
            @Override
            public void onActivityResumed(Activity a) { }
            @Override
            public void onActivityPaused(Activity a) { }
            @Override
            public void onActivitySaveInstanceState(Activity a, Bundle b) { }
            @Override
            public void onActivityDestroyed(Activity a) { }
        });
    }
}
