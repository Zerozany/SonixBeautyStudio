package com.zerosystem.system;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.Intent;
import android.net.Uri;
import android.provider.Settings;
import android.util.Log;
import com.zerosystem.utiles.MessageUtile;

public class SystemControl {
    private Activity m_activity;

    public SystemControl(Activity _activity)
    {
        init(_activity);
    }

    private void init(Activity _activity)
    {
        this.m_activity = _activity;
        if (!Settings.System.canWrite(m_activity)) {
            Intent intent = new Intent(Settings.ACTION_MANAGE_WRITE_SETTINGS);
            intent.setData(Uri.parse("package:" + m_activity.getPackageName()));
            m_activity.startActivity(intent);
        }
    }

    /**
     * 设置系统全局亮度 0~255
     */
    public void setSystemBrightness(final int brightness)
    {
        if (m_activity == null) {
            return;
        }
        try {
            // 检查是否有权限修改系统设置
            if (!Settings.System.canWrite(m_activity)) {
                Log.w(MessageUtile.HandleDebug, "[AppSettings.java] No WRITE_SETTINGS permission!");
                return;
            }
            ContentResolver resolver = m_activity.getContentResolver();
            int value = Math.max(0, Math.min(brightness, 255));
            Settings.System.putInt(resolver, Settings.System.SCREEN_BRIGHTNESS, value);
        } catch (Exception e) {
            Log.e(MessageUtile.HandleDebug, "[AppSettings.java] Failed to set system brightness", e);
        }
    }

    /**
     * 获取系统全局亮度 0~255
     */
    public int getSystemBrightness()
    {
        if (m_activity == null) {
            return -1;
        }
        try {
            ContentResolver resolver = m_activity.getContentResolver();
            return Settings.System.getInt(resolver, Settings.System.SCREEN_BRIGHTNESS);
        } catch (Settings.SettingNotFoundException e) {
            Log.e(MessageUtile.HandleDebug, "[AppSettings.java] Failed to get system brightness", e);
            return -1;
        }
    }
}
