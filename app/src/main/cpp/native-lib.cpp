#include <jni.h>
#include <string>
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
