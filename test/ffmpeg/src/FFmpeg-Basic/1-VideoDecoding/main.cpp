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

    if (videoDecoding.findStreamIndex())
    {
        return 1;
    }

    // Initialize the AVCodecContext
    if (videoDecoding.initCodecContext())
    {
        return 1;
    }

    videoDecoding.readFrameProc();

    // //Init variable
    // int streamIndex = -1;
    // AVFormatContext *formatCtx = NULL;
    // AVCodecContext *codecCtx = NULL;
    // //open input file
    // if (avformat_open_input(&formatCtx, fileName, 0, 0) < 0)
    // {
    //     printf("Failed to open input file!\n");
    //     return 0;
    // }
    // //get stream info
    // if (avformat_find_stream_info(formatCtx, 0) < 0)
    // {
    //     printf("Failed to find stream info!\n");
    //     return 0;
    // }
    // //get video stream
    // streamIndex = av_find_best_stream(formatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    // if (streamIndex < 0)
    // {
    //     printf("Failed to find video stream!\n");
    //     return 0;
    // }
    // //get codec context
    // //find decoder
    // AVCodec *codec = avcodec_find_decoder(formatCtx->streams[streamIndex]->codecpar->codec_id);
    // //Allocate a codec context for decoder
    // codecCtx = avcodec_alloc_context3(codec);
    // //Fill the codec contex based on the supplied codec parameters.
    // if (avcodec_parameters_to_context(codecCtx, formatCtx->streams[streamIndex]->codecpar) < 0)
    // {
    //     printf("Failed to transfer params to codec context!\n");
    //     return 0;
    // }
    // //Initialize the AVCodecContext to use the given Codec
    // if (avcodec_open2(codecCtx, codec, 0) < 0)
    // {
    //     printf("Failed to init context for given codec!\n");
    //     return 0;
    // }
    // //Read frame
    // //Alloc frame
    // AVPacket packet;
    // AVFrame *frame = av_frame_alloc();
    // //Make output file path
    // char output[40] = {0};
    // int outputWidth = formatCtx->streams[streamIndex]->codecpar->width;
    // int outputHeight = formatCtx->streams[streamIndex]->codecpar->height;
    // sprintf(output, "../output/Sample1_%dx%d_yuv420p.yuv", outputWidth, outputHeight);

    // FILE *fs = fopen(output, "wb");
    // //Traverse throught frame array to find video packet
    // while (int i = av_read_frame(formatCtx, &packet) >= 0)
    // {

    //     //Find packet with stream index
    //     if (packet.stream_index == streamIndex)
    //     {
    //         //Decode video
    //         //send packet to codec
    //         if (avcodec_send_packet(codecCtx, &packet) < 0)
    //         {
    //             printf("Failed to copy codec context to packet!\n");
    //         }
    //         //receive framem from codec
    //         int ret = avcodec_receive_frame(codecCtx, frame);
    //         if (!ret)
    //         {

    //             //Save output file
    //             fwrite(frame->data[0], 1, codecCtx->width * codecCtx->height, fs);
    //             fwrite(frame->data[1], 1, codecCtx->width * codecCtx->height / 4, fs);
    //             fwrite(frame->data[2], 1, codecCtx->width * codecCtx->height / 4, fs);
    //         }
    //     }
    //     av_packet_unref(&packet);
    // }
    // //Close output write stream
    // fclose(fs);
    // printf("Decoded file successfully!\n");
    // //Remove codec context alloc
    // avcodec_free_context(&codecCtx);
    // //Close input file
    // avformat_close_input(&formatCtx);
    return 1;
}
