package com.sonixbeauty.system;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.os.Build;
import android.util.Log;

public class UsbPermissionManager {

    private static final String ACTION_USB_PERMISSION = "com.sonixbeauty.USB_PERMISSION";

    // ===== 单例 =====
    private static volatile UsbPermissionManager instance;

    public static UsbPermissionManager getInstance()
    {
        if (instance == null) {
            synchronized (UsbPermissionManager.class) {
                if (instance == null) {
                    instance = new UsbPermissionManager();
                }
            }
        }
        return instance;
    }

    private UsbManager usbManager;
    private PendingIntent permissionIntent;
    private Context context;

    // ===== JNI 回调 =====
    public static native void onUsbPermissionResult(boolean granted);

    private UsbPermissionManager() { }

    // ===== 初始化（只调用一次）=====
    public void init(Activity activity)
    {
        this.context = activity.getApplicationContext();

        usbManager = (UsbManager)activity.getSystemService(Context.USB_SERVICE);

        permissionIntent = PendingIntent.getBroadcast(
            activity,
            0,
            new Intent(ACTION_USB_PERMISSION),
            Build.VERSION.SDK_INT >= 23
                ? PendingIntent.FLAG_IMMUTABLE
                : 0);

        registerReceiver();
    }

    // ===== 注册广播（内部管理）=====
    private void registerReceiver()
    {
        IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);

        context.registerReceiver(usbReceiver, filter);
    }

    // ===== 请求权限 =====
    public void requestPermission(UsbDevice device)
    {
        if (usbManager != null && device != null) {
            usbManager.requestPermission(device, permissionIntent);
        }
    }

    // ===== USB 回调 =====
    private final BroadcastReceiver usbReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent)
        {

            if (ACTION_USB_PERMISSION.equals(intent.getAction())) {

                UsbDevice device = intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);

                boolean granted = intent.getBooleanExtra(
                    UsbManager.EXTRA_PERMISSION_GRANTED,
                    false);

                Log.d("USB", "permission result = " + granted);

                onUsbPermissionResult(granted);
            }
        }
    };

    // ===== 自动销毁（由系统/进程结束触发）=====
    public void destroy()
    {
        try {
            context.unregisterReceiver(usbReceiver);
        } catch (Exception ignored) {
        }

        instance = null;
    }
}
