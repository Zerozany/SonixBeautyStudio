package com.zerosystem.core;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import com.zerosystem.utiles.MessageUtile;

public class SplashActivity extends Activity {

    @Override
    public void onCreate(Bundle _savedInstanceState)
    {
        super.onCreate(_savedInstanceState);
        Intent intent = new Intent(this, MainActivity.class);
        intent.setFlags(Intent.FLAG_ACTIVITY_NO_ANIMATION);
        intent.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        startActivity(intent);
    }
}
