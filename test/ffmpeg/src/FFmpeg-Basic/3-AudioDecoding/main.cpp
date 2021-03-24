/*
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 */

#include "AudioDecoding.h"

//g++ -w main.cpp AudioDecoding.cpp -o main $(pkg-config --cflags --libs libavutil libavformat libavcodec)
int main(int argc, char **argv)
{
    AudioDecoding audioDecoding;

    // play command: ffplay -f s16le -ac 2 -ar 44100 out.pcm
    const char *fileName = "../assets/Sample.mkv";

    // play command: ffplay -f f32le -ac 2 -ar 44100 out.pcm
    //const char *fileName = "../assets/echo.aac";

    // if (audioDecoding.init(fileName))
    //     return 1;

    // if (audioDecoding.initCodecContext())
    //     return 1;
    // if (audioDecoding.readFrameProc())
    //     return 1;

    AVFormatContext *formatContext = NULL;
    AVCodecContext *codecContext = NULL;
    int streamIndex = -1;

    if (avformat_open_input(&formatContext, fileName, 0, 0) < 0)
    {
        printf("Failed to open input\n");
        return 1;
    }
    if (avformat_find_stream_info(formatContext, 0) < 0)
    {
        printf("Can not find stream info in format context\n");
        return 1;
    }
    av_dump_format(formatContext, 0, fileName, 0);
    streamIndex = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (!streamIndex)
    {
        printf("Can not find audio stream\n");
        return 1;
    }

    AVCodec *codec = avcodec_find_decoder(formatContext->streams[streamIndex]->codecpar->codec_id);
    if (!codec)
    {
        printf("Can not find decoder\n");
        return 1;
    }
    codecContext = avcodec_alloc_context3(codec);
    if (!codecContext)
    {
        printf("Failed to alloc codec context\n");
        return 1;
    }
    if (avcodec_parameters_to_context(codecContext, formatContext->streams[streamIndex]->codecpar) < 0)
    {
        printf("Failed to transfer format params to context\n");
        return 1;
    }
    if (avcodec_open2(codecContext, codec, 0) < 0)
    {
        printf("Failed to init codec context\n");
        return 1;
    }
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    if (!frame)
    {
        printf("Failed to alloc frame\n");
        return 1;
    }
    char output[40] = {0};
    sprintf(output, "../output/out1.pcm");
    FILE *outputfs = fopen(output, "wb");
    while (int i = av_read_frame(formatContext, &packet) >= 0)
    {
        if (packet.stream_index == streamIndex)
        {
            avcodec_send_packet(codecContext, &packet);
            int ret = avcodec_receive_frame(codecContext, frame);
            if (!ret)
            {
                int sampleBytes = av_get_bytes_per_sample(codecContext->sample_fmt);

                // write audio file for Planar sample format
                for (int i = 0; i < frame->nb_samples; i++)
                    for (int ch = 0; ch < codecContext->channels; ch++)
                        fwrite(frame->data[ch] + sampleBytes * i, 1, sampleBytes, outputfs);
            }
        }
        av_packet_unref(&packet);
    }
    av_frame_free(&frame);
    fclose(outputfs);
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);
    printf("Save out1.pcm successfully!\n");
    return 0;
}