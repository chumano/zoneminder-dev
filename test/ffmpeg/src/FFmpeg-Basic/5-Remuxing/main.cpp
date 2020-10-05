/*
 * Copyright (c) 2017 Liming Shao <lmshao@163.com>
 */

#include "Remuxing.h"

//g++ -w main.cpp Remuxing.cpp -o main $(pkg-config --cflags --libs libavutil libavformat libavcodec)
int main()
{
    // Remuxing remuxing;

    // Just to modefy the suffix (mkv/ts/mp4).
    //rtsp://admin:Tris@123@chumano.ddns.net:55401/h264/main/av_stream
    const char *inFile = "../assets/Sample.mkv";
    const char *outFile = "../output/Sample.mp4";

    // if (remuxing.init(inFile, outFile))
    //     return 1;

    // // Configure AVCodecContext parameters Manually
    // if (remuxing.initOutFmtCtx())
    //     return 1;

    // if (remuxing.transferMediaStream())
    //     return 1;

    // return 0;

    //Declare variable
    AVFormatContext *inFormatContext = NULL;
    AVFormatContext *outFormatContext = NULL;
    int numberOfStreams = -1;
    int *streamMap;

    // Get input file format context
    // AVDictionary *opts = 0;
    // if (av_dict_set(&opts, "rtsp_transport", "tcp", 0) < 0)
    // {
    //     printf("Could not set rtsp_transport method");
    // }
    // printf("Number of dictionary entries: %i\n", av_dict_count(opts));
    inFormatContext = avformat_alloc_context();
    if (avformat_open_input(&inFormatContext, inFile, NULL, NULL) < 0)
    {
        printf("Failed to get input format context\n");
        return 1;
    }

    // AVDictionaryEntry *e = NULL;
    // while ((e = av_dict_get(opts, "", e, AV_DICT_IGNORE_SUFFIX)) != NULL)
    // {
    //     printf("Option %s not recognized by ffmpeg", e->key);
    // }
    // av_dict_free(&opts);
    if (avformat_find_stream_info(inFormatContext, 0) < 0)
    {
        printf("Failed to find stream info in input format context\n");
        return 1;
    }

    // Finish get input file format context
    av_dump_format(inFormatContext, 0, inFile, 0);

    //Setup output file format context
    if (avformat_alloc_output_context2(&outFormatContext, 0, 0, outFile) < 0)
    {
        printf("Failed to alloc output format context\n");
        return 1;
    }

    numberOfStreams = inFormatContext->nb_streams;
    streamMap = (int *)av_mallocz_array(numberOfStreams, sizeof(streamMap));
    if (!streamMap)
    {
        printf("Failed to alloc stream map\n");
        return 1;
    }

    // Map media stream
    int streamIdx = 0;
    for (int i = 0; i < inFormatContext->nb_streams; i++)
    {
        AVCodecParameters *codecParams = inFormatContext->streams[i]->codecpar;
        //check stream type
        if (codecParams->codec_type != AVMEDIA_TYPE_AUDIO &&
            codecParams->codec_type != AVMEDIA_TYPE_VIDEO &&
            codecParams->codec_type != AVMEDIA_TYPE_SUBTITLE)
        {
            streamMap[i] = -1;
            continue;
        }
        streamMap[i] = streamIdx++;

        // Add a new stream to a media file
        AVStream *newStream = avformat_new_stream(outFormatContext, 0);
        if (!newStream)
        {
            printf("Faild to add new stream to output format context\n");
        }

        // copy the contents of src to dst
        if (avcodec_parameters_copy(newStream->codecpar, codecParams) < 0)
        {
            printf("Failed to copy c odec params to new stream\n");
        }

        newStream->codecpar->codec_tag = 0;
    }
    //Finish setup output format context
    av_dump_format(outFormatContext, 0, outFile, 1);
    // Transfer media
    //check output format flag
    AVOutputFormat *outFormat = outFormatContext->oformat;
    if (!(outFormat->flags & AVFMT_NOFILE))
    {
        if (avio_open(&outFormatContext->pb, outFile, AVIO_FLAG_WRITE))
        {
            printf("Failed to open output file\n");
        }
    }
    //write header
    if (avformat_write_header(outFormatContext, 0) < 0)
    {
        printf("Error while writing output file\n");
    }

    //write content
    AVPacket packet;
    while (1)
    {
        AVStream *inStream, *outStream;
        //read frame
        if (av_read_frame(inFormatContext, &packet) < 0)
        {
            break;
        }
        inStream = inFormatContext->streams[packet.stream_index];

        //check stream index
        if (packet.stream_index >= numberOfStreams | streamMap[packet.stream_index] < 0)
        {
            av_packet_unref(&packet);
            continue;
        }

        //map stream index to output stream
        packet.stream_index = streamMap[packet.stream_index];
        outStream = outFormatContext->streams[packet.stream_index];

        //copy packet
        printf("packet pts: %" PRIu64 "\n", packet.pts);
        packet.pts = av_rescale_q_rnd(packet.pts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        packet.dts = av_rescale_q_rnd(packet.dts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        packet.duration = av_rescale_q(packet.duration, inStream->time_base, outStream->time_base);
        packet.pos = 1;
        // printf("outStream time_base: %i/%i\n", outStream->time_base.num, outStream->time_base.den);
        // printf("packet pts: %" PRIu64 "\n", packet.pts);
        // printf("packet dts: %" PRIu64 "\n", packet.dts);
        // printf("packet duration: %" PRIu64 "\n", packet.duration);

        //write frame
        if (av_interleaved_write_frame(outFormatContext, &packet) < 0)
        {
            printf("Error muxing\n");
            break;
        }
        av_packet_unref(&packet);
    }
    //write trailer
    av_write_trailer(outFormatContext);

    //Finish transfer
    avio_closep(&outFormatContext->pb);
    avformat_free_context(outFormatContext);
    avformat_close_input(&inFormatContext);

    printf("Muxing completed\n");
    return 0;
}