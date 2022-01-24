#include <jni.h>
#include <string>
#include "Mp4Player.h"
extern "C"{
#include "test.h"
#include "libavformat/avformat.h"
#include "libavutil/avstring.h"
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_xhc_android_1ffmepg2_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    test();
    av_register_all();
    AVFormatContext *afc = NULL;
    int flag = avformat_open_input(&afc ,"https://tudou.mrxxhc.cn/ts/test.webm" , NULL , NULL );

    return env->NewStringUTF(hello.c_str());
}

Mp4Player *mp4Player = NULL;
CallJava *cj = NULL;


void custom_log(void *ptr, int level, const char *fmt, va_list vl) {
//    FILE *fp = fopen("sdcard/FFmpeg/ffmpeg_log.txt", "a+");
//    if (fp) {
//        vfprintf(fp, fmt, vl);
//        fflush(fp);
//        fclose(fp);
//    }
    char str[1024 * 2];
    vsprintf(str , fmt , vl);
    LOGFFMPEG("%s", str);

};

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_initMp4Play(JNIEnv *env, jclass type,
                                                              jstring path_,
                                                              jobject glSurfaceView) {
    // TODO: implement initMp4Play()
    if (mp4Player == NULL) {
        if (cj == NULL) {
            cj = new CallJava(env, type);
        }
        jboolean flag = 0;
        const char *path = env->GetStringUTFChars(path_, &flag);
        ANativeWindow *win = ANativeWindow_fromSurface(env, glSurfaceView);
        av_log_set_callback(custom_log);
        mp4Player = new Mp4Player(path, win, cj);
        env->ReleaseStringUTFChars(path_, path);
    }
    return 1;
}


extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getDuration(JNIEnv *env, jclass clazz) {
    // TODO: implement getDuration()
    if (mp4Player != NULL) {
        return mp4Player->getDuration();
    }
    return -1;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_destroyMp4Play(JNIEnv *env, jclass clazz) {
    // TODO: implement destroyMp4Play()
    if (mp4Player != NULL) {
        delete mp4Player;

    }
    mp4Player = NULL;
    if (cj != NULL) {
        delete cj;
    }
    cj = NULL;
    return 1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_mp4Pause(JNIEnv *env, jclass clazz) {
    // TODO: implement mp4Pause()
    if (mp4Player != NULL) {
        mp4Player->pauseVA();
        return 1;
    }

    return -1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_mp4Play(JNIEnv *env, jclass clazz) {
    // TODO: implement mp4Play()
    if (mp4Player != NULL) {
        mp4Player->playVA();
        return 1;
    }
    return -1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getProgress(JNIEnv *env, jclass clazz) {
    // TODO: implement getProgress()
    if (mp4Player != NULL) {
        return mp4Player->getProgress();
    }
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_changeSpeed(JNIEnv *env, jclass clazz,
                                                              jfloat speed) {
    // TODO: implement changeSpeed()
    if (mp4Player != NULL) {
        mp4Player->changeSpeed(speed);
        return 1;
    }
    return -1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_seekStart(JNIEnv *env, jclass clazz) {
    // TODO: implement seekStart()
    if (mp4Player != NULL) {
        mp4Player->seekStart();
    }
    return 1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_seek(JNIEnv *env, jclass clazz, jfloat progress) {
    // TODO: implement seek()
    if (mp4Player != NULL) {
        mp4Player->seek(progress);
    }
    return 1;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getVideoWidth(JNIEnv *env, jclass clazz) {
    // TODO: implement getVideoWidth()
    // TODO
    if (mp4Player != NULL) {
        return mp4Player->getVideoWidth();
    }
    return 0;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getVideoHeight(JNIEnv *env, jclass clazz) {
    // TODO: implement getVideoHeight()
    // TODO
    if (mp4Player != NULL) {
        return mp4Player->getVideoHeight();
    }
    return 0;
}

int parseTime(struct tm* tm2 , char **str){
    char tmp[100];
    memset(tmp , 0, 100);
    sprintf(tmp , "%d%02d%02dT%02d%02d%02dZ" , tm2->tm_year+1900 ,tm2->tm_mon + 1 , tm2->tm_mday , tm2->tm_hour , tm2->tm_min  , tm2->tm_sec);
    av_strlcpy(*str , tmp , strlen(tmp) + 1);
    return 1 ;
}

//用我们1970 转换出来的时间需要+ 1900 ，mon +1
//用正常tm转换的时间不需要 mon + 1
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_test(JNIEnv *env, jclass clazz) {
    // TODO: implement test()
    const char *url = "http:192.168.98.147:8080/hls/play.m3u8?livemode=2&starttime=20220112T002651Z&other=test";




//    const char* date = "20280112T002653Z";
//    char *startTime = av_stristr(url , "starttime=");
//    LOGE(" %d " , startTime - url);
//    char dstUrl[1024 * 2];
//    memset(dstUrl , 0 , 1024 * 2);
//    av_strlcpy(dstUrl , url , startTime - url);
////    const char *ptr = NULL ;
////    av_strstart(startTime, "starttime=" , &ptr);
////    av_strlcpy(startTime + strlen("starttime=") , date , strlen(date)+1);
//    LOGE("%s " , dstUrl  );
//    char newUrl[1024 * 2];
//    memset(newUrl , 0 , 1024 * 2);
//    sprintf(newUrl,"%s%s%s" , dstUrl ,"&starttime=" , date);
//    LOGE("%s " , newUrl);
//
//    struct tm tm_;
//    char *startTime = av_stristr(url , "starttime=");
//    LOGE("strttime %s" , startTime);
//    const char *ptr = NULL ;
//    av_strstart(startTime, "starttime=" , &ptr);
//    LOGE("strttime %s ， strlen %d " , ptr , strlen(ptr));
//    char tmp[100];
//    memset(tmp , 0, 100);
//    av_strlcpy(tmp , ptr , 5);
//    tm_.tm_year = atoi(tmp);
//    LOGE("year %s , %d " , tmp  , tm_.tm_year);
//
//    memset(tmp , 0, 100);
//    av_strlcpy(tmp , ptr+4 , 3);
//    tm_.tm_mon = atoi(tmp) - 1;
//    LOGE("mon %s , %d " , tmp  , tm_.tm_mon);
//
//    memset(tmp , 0, 100);
//    av_strlcpy(tmp , ptr+6 , 3);
//    tm_.tm_mday = atoi(tmp);
//    LOGE("day %s , %d " , tmp  , tm_.tm_mday);
//
//    memset(tmp , 0, 100);
//    av_strlcpy(tmp , ptr+9 , 3);
//    tm_.tm_hour = atoi(tmp);
//    LOGE("hour %s , %d " , tmp  , tm_.tm_hour);
//
//    memset(tmp , 0, 100);
//    av_strlcpy(tmp , ptr+11 , 3);
//    tm_.tm_min = atoi(tmp);
//    LOGE("min %s , %d " , tmp  , tm_.tm_min);
//
//    memset(tmp , 0, 100);
//    av_strlcpy(tmp , ptr+13 , 3);
//    tm_.tm_sec = atoi(tmp);
//    LOGE("sec %s , %d " , tmp  , tm_.tm_sec);
//
//    tm_.tm_year -= 1900;
//    time_t t = mktime(&tm_); // 这里得到的是什么时间，多了一个月
//    LOGE("time %d " , t);

//    struct tm* tm2 = localtime(&t);
//    memset(tmp , 0, 100);
//    sprintf(tmp , "%d%02d%02dT%02d%02d%02dZ" , tm2->tm_year+1900 ,tm2->tm_mon  , tm2->tm_mday , tm2->tm_hour , tm2->tm_min  , tm2->tm_sec);
//    LOGE("%s" ,tmp);
//
//    time_t t2 = 1652326011; //传入的就是1970 的时间
//                //1644632811
//    int64_t time = 1652326011;
//    struct tm* tm4 = localtime((const time_t*)&time);
//    char *str = (char *)malloc(100);
//    parseTime(tm4 , &str);
//    LOGE("parse time %s" , str);
    return 1;
}






















