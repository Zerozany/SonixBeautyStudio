package com.sonixbeauty.drive;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;
import android.util.Log;
import com.sonixbeauty.utiles.SonixUtiles;

public class ActivityControl implements Application.ActivityLifecycleCallbacks {

    private static native void NotifyRestart();
    private static native void NotifyPause();

    private int activityReferences = 0;
    private boolean isConfigChanged = false;

    @Override
    public void onActivityStarted(Activity activity)
    {
        if (++activityReferences == 1 && !isConfigChanged) {
            Log.d(SonixUtiles.SonixDebug, "App enters foreground");
            NotifyRestart(); // 调用 Qt 层
        }
    }

    @Override
    public void onActivityStopped(Activity activity)
    {
        isConfigChanged = activity.isChangingConfigurations();
        if (--activityReferences == 0 && !isConfigChanged) {
            Log.d(SonixUtiles.SonixDebug, "App enters background");
            NotifyPause(); // 调用 Qt 层
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
}
