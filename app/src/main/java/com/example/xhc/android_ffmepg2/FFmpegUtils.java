package com.example.xhc.android_ffmepg2;

import android.text.TextUtils;

import java.util.ArrayList;
import java.util.List;

public class FFmpegUtils {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
        System.loadLibrary("ffmpeg");

    }

    private static List<Lis> listNativeNotify = new ArrayList<>();

    public static void addNativeNotify(Lis lis){
        listNativeNotify.add(lis);
    }

    public static void removeNotify(Lis lis){
        listNativeNotify.remove(lis);
    }

    public interface Lis{
        void nativeNotify(String str);
    }

    //下面是做音视频播放器的
    public static native int initMp4Play(String path, Object glSurfaceView);
    public static native float getDuration();
    public static native int destroyMp4Play();
    public static native int mp4Pause();
    public static native int mp4Play();
    public static native int getProgress();
    public static native int changeSpeed(float speed);
    public static native int seekStart();
    public static native int seek(float progress);
    public static native int getVideoWidth();
    public static native int getVideoHeight();


    //判断本地回调的数据是否是用来显示的
    public static boolean isShowToastMsg(String msg){
        if(TextUtils.isEmpty(msg)){
            return false;
        }
        if(msg.startsWith("metadata")){
            return false;
        }
        return true;
    }
}
