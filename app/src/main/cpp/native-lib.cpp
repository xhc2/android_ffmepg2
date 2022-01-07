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
CallJava *cj = NULL;

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