package com.example.xhc.android_ffmepg2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        FFmpegUtils.test();
//        Intent intent =new Intent(MainActivity.this , Mp4PlayerActivity.class);
//        intent.putExtra("path" , "http://220.161.87.62:8800/hls/0/index.m3u8");
//        startActivity(intent);
//        finish();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
