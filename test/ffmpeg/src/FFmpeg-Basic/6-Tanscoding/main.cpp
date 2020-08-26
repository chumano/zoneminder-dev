/*
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 */

#include "Transcoding.h"
#include <stdio.h>

// unfinished
//g++ -w main.cpp Transcoding.cpp -o main $(pkg-config --cflags --libs libavutil libavformat libavcodec libavfilter)
int main()
{
    const char *srcFile = "../assets/Sample.mkv";
    const char *dstFile = "../output/Sample.mp4";

    Transcoding tc;

    tc.initSys();

    if (tc.initDecCtx(srcFile))
    {
        printf("Failed to init decodec ctx");
        return 1;
    }

    if (tc.initEncCtx(dstFile))
    {
        printf("Failed to init encodec ctx");
        return 1;
    }

    if (tc.initFilters())
    {
        printf("Failed to init filters");
        return 1;
    }

    if (tc.transcode())
    {
        printf("Err.");
        return 1;
    }

    return 0;
}