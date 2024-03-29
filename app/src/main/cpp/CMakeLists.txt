# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.


message(AUTHOR_WARNING "++++++++++++++++ main MY_INCLUDE_PATH  ${CMAKE_SOURCE_DIR}")

add_subdirectory(${CMAKE_SOURCE_DIR}/ffmpeg/ffmpeg_src/ ffmpeg.out)
include_directories(
        ${CMAKE_SOURCE_DIR}/ffmpeg/ffmpeg_src/
        ${CMAKE_SOURCE_DIR}/
)

add_library(
             native-lib

             SHARED
        AudioPlayer.cpp
        DecodeMyAudioThread.cpp
        DecodeVideoThread.cpp
        Mp4Player.cpp
        MyData.cpp
        MyThread.cpp
        NewAudioPlayer.cpp
        ReadAvPacket.cpp
        sonic.cpp
        SonicRead.cpp
        Utils.cpp
        YuvPlayer.cpp
        CallJava.cpp
        Notify.cpp
        SeekVideo.cpp
        CPP_shareptr.cpp
        native-lib.cpp )


find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
find_library( # Sets the name of the path variable.
        zlib-lib

        z )
#enable_language(ASM)
# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib
                        ffmpeg
                        OpenSLES
                        EGL
                        GLESv2
                        android
                        log
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                        ${zlib-lib})