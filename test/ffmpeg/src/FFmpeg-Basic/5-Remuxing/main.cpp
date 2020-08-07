/*
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 */

#include "Remuxing.h"

//g++ -w main.cpp Remuxing.cpp -o main $(pkg-config --cflags --libs libavutil libavformat libavcodec)
int main()
{
    Remuxing remuxing;

    // Just to modefy the suffix (mkv/ts/mp4).
    const char *inFile = "../assets/Sample.mkv";
    const char *outFile = "../output/Sample.mp4";

    if (remuxing.init(inFile, outFile))
        return 1;

    // Configure AVCodecContext parameters Manually
    if (remuxing.initOutFmtCtx())
        return 1;

    if (remuxing.transferMediaStream())
        return 1;

    return 0;
}