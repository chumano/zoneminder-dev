/*
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 */

#include "VideoDecoding.h"

//g++ -w main.cpp VideoDecoding.cpp -o main $(pkg-config --cflags --libs libavutil libavformat libavcodec)
int main()
{
    const char *fileName = "../assets/Sample.mkv";

    VideoDecoding videoDecoding;

    videoDecoding.init(fileName);

    if (videoDecoding.findStreamIndex()) {
        return 1;
    }

    // Initialize the AVCodecContext
    if (videoDecoding.initCodecContext()) {
        return 1;
    }

    videoDecoding.readFrameProc();
}
