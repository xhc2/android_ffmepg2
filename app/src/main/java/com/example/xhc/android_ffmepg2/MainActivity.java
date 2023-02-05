package com.example.xhc.android_ffmepg2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

/*
* 1.hls 请求m3u8请求逻辑，并一个targetduration的方式来处理，处理失败再确认重试逻辑。
Hls.c 刷新逻辑在 read_data 中，有现成的时间间隔函数。后续可以再这里处理。但是异常处理逻辑还需要确认。

2.防浪涌的逻辑还是要放在hls中处理。
在请求m3u8 或者 ts 失败根据返回值再重新请求m3u8。vod 还需要确定seek 到指定为止


http 中的urlcontext hd 就是tcp 的context ，直接使用即可。

nginx rewrite

*
* */
public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        FFmpegUtils.test();
        Intent intent =new Intent(MainActivity.this , Mp4PlayerActivity.class);
//        intent.putExtra("path" , "http://devimages.apple.com/iphone/samples/bipbop/gear1/prog_index.m3u8");
        intent.putExtra("path" , "http://220.161.87.62:8800/hls/0/index.m3u8");
//        intent.putExtra("path" , "http://192.168.1.3");
        startActivity(intent);
        finish();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

}
