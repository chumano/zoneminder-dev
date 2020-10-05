#include <stdio.h>
#include <cstdlib>
#include <sys/stat.h>
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
}

using namespace std;

int main(int argc, char *argv[])
{
    double fps = 2.0;
    int eventid = 15;

    const char *videoPath = "/src/FFmpeg-Test/assets/15/15-video.mp4";
    static unsigned char temp_img_buffer[(2048 * 1536) * 4];

    //send frame from file mp4
    AVFormatContext *inFormatCtx = NULL;
    AVFormatContext *outFormatCtx = NULL;
    AVCodecContext *inCodecCtx;
    AVCodecContext *outCodecCtx;
    int mVideoStreamIndex;
    //init video input format
    if ((avformat_open_input(&inFormatCtx, videoPath, 0, 0)) < 0)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Failed to open input file\n");
    }

    if ((avformat_find_stream_info(inFormatCtx, 0)) < 0)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Failed to retrieve input stream information\n");
    }

    mVideoStreamIndex = av_find_best_stream(inFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (mVideoStreamIndex < 0)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Could not find stream in input file\n");
        return true;
    }

    AVCodec *dec = avcodec_find_decoder(inFormatCtx->streams[mVideoStreamIndex]->codecpar->codec_id);
    if (!dec)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Failed to find codec!\n");
        return true;
    }

    // Allocate a codec context for the decoder
    if (!(inCodecCtx = avcodec_alloc_context3(dec)))
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Failed to allocate the codec context\n");
        return true;
    }

    // Fill the codec contex based on the supplied codec parameters.
    if (avcodec_parameters_to_context(inCodecCtx, inFormatCtx->streams[mVideoStreamIndex]->codecpar) < 0)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Failed to copy codec parameters to decoder context!\n");
        return true;
    }

    // Initialize the AVCodecContext to use the given Codec
    if (avcodec_open2(inCodecCtx, dec, NULL) < 0)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Failed to open codec\n");
        return true;
    }

    //init jpeg format context
    //Create a jpg file just to get the correct codec, not really write into the file
    const char *outFile = "/src/FFmpeg-Test/output/stream.jpg";
    outFormatCtx = avformat_alloc_context();
    avformat_alloc_output_context2(&outFormatCtx, NULL, NULL, outFile);
    // av_dump_format(outFormatCtx, 0, outFile, 1);

    //init jpeg encoder context
    int tmpW = inFormatCtx->streams[mVideoStreamIndex]->codecpar->width;
    int tmpH = inFormatCtx->streams[mVideoStreamIndex]->codecpar->height;
    outCodecCtx = avcodec_alloc_context3(NULL);
    outCodecCtx->codec_id = outFormatCtx->oformat->video_codec;
    outCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    outCodecCtx->pix_fmt = AV_PIX_FMT_YUVJ420P;
    outCodecCtx->width = tmpW;
    outCodecCtx->height = tmpH;
    outCodecCtx->time_base.num = 1;
    outCodecCtx->time_base.den = 25;

    AVCodec *pCodec = avcodec_find_encoder(outCodecCtx->codec_id);
    if (!pCodec)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Codec not found\n");
        return -1;
    }

    if (avcodec_open2(outCodecCtx, pCodec, NULL) < 0)
    {
        fputs("Content-Type: text/html\r\n\r\n", stdout);
        printf("Could not open codec\n");
        return -1;
    }

    // read frame from video
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    AVPacket *jpg_packet = av_packet_alloc();

    fputs("Content-Type: multipart/x-mixed-replace;boundary=ZoneMinderFrame\r\n\r\n", stdout);
    while (av_read_frame(inFormatCtx, &packet) >= 0)
    {
        if (packet.stream_index == mVideoStreamIndex)
        {
            avcodec_send_packet(inCodecCtx, &packet);
            int ret = avcodec_receive_frame(inCodecCtx, frame);
            if (ret == 0)
            {
                avcodec_send_frame(outCodecCtx, frame);
                int ret = avcodec_receive_packet(outCodecCtx, jpg_packet);
                if (ret == 0)
                {
                    fprintf(stdout, "--ZoneMinderFrame\r\n");
                    fputs("Content-Type: image/jpeg\r\n", stdout);
                    fprintf(stdout, "Content-Length: %d\r\n\r\n", (int)jpg_packet->size);
                    fwrite(jpg_packet->data, jpg_packet->size, 1, stdout);
                    fputs("\r\n\r\n", stdout);
                    fflush(stdout);
                }
                av_packet_unref(jpg_packet);
            }
        }
        av_packet_unref(&packet);
        // break;
    }

    //End danger
    avcodec_free_context(&inCodecCtx);
    avformat_close_input(&inFormatCtx);
    avcodec_free_context(&outCodecCtx);
    avformat_free_context(outFormatCtx);
    av_packet_free(&jpg_packet);
    remove(outFile);

    return true;
}