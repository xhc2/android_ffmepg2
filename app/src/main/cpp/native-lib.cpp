#include <jni.h>
#include <string>
#include "Mp4Player.h"
extern "C"{
#include "test.h"
#include "libavformat/avformat.h"
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

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_initMp4Play(JNIEnv *env, jclass clazz,
                                                              jstring path,
                                                              jobject gl_surface_view) {
    // TODO: implement initMp4Play()
}


extern "C"
JNIEXPORT jfloat JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getDuration(JNIEnv *env, jclass clazz) {
    // TODO: implement getDuration()
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_destroyMp4Play(JNIEnv *env, jclass clazz) {
    // TODO: implement destroyMp4Play()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_mp4Pause(JNIEnv *env, jclass clazz) {
    // TODO: implement mp4Pause()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_mp4Play(JNIEnv *env, jclass clazz) {
    // TODO: implement mp4Play()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getProgress(JNIEnv *env, jclass clazz) {
    // TODO: implement getProgress()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_changeSpeed(JNIEnv *env, jclass clazz,
                                                              jfloat speed) {
    // TODO: implement changeSpeed()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_seekStart(JNIEnv *env, jclass clazz) {
    // TODO: implement seekStart()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_seek(JNIEnv *env, jclass clazz, jfloat progress) {
    // TODO: implement seek()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getVideoWidth(JNIEnv *env, jclass clazz) {
    // TODO: implement getVideoWidth()
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_xhc_android_1ffmepg2_FFmpegUtils_getVideoHeight(JNIEnv *env, jclass clazz) {
    // TODO: implement getVideoHeight()
}