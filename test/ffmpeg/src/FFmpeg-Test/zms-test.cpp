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

const string ENV[24] = {
    "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE", "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING", "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION", "HTTP_HOST", "HTTP_USER_AGENT", "PATH", "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT", "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME", "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN", "SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL", "SERVER_SIGNATURE", "SERVER_SOFTWARE"};

int main(int argc, char *argv[])
{
    double fps = 2.0;
    int eventid = 15;

    // const char *query = getenv("QUERY_STRING");
    // char temp_query[1024];
    // strncpy(temp_query, query, sizeof(temp_query) - 1);
    // char *q_ptr = temp_query;
    // char *parms[16]; // Shouldn't be more than this
    // int parm_no = 0;
    // while ((parm_no < 16) && (parms[parm_no] = strtok(q_ptr, "&")))
    // {
    //     parm_no++;
    //     q_ptr = NULL;
    // }

    // for (int p = 0; p < parm_no; p++)
    // {
    //     char *name = strtok(parms[p], "=");
    //     char const *value = strtok(NULL, "=");
    //     if (!value)
    //         value = "";
    //     if (!strcmp(name, "fps"))
    //     {
    //         fps = atof(value);
    //     }
    //     if (!strcmp(name, "event"))
    //     {
    //         eventid = atoi(value);
    //     }
    //   if ( !strcmp(name, "source") ) {
    //     source = !strcmp(value, "event")?ZMS_EVENT:ZMS_MONITOR;
    //     if ( !strcmp(value, "fifo") )
    //       source = ZMS_FIFO;
    //   } else if ( !strcmp(name, "mode") ) {
    //     mode = !strcmp(value, "jpeg")?ZMS_JPEG:ZMS_MPEG;
    //     mode = !strcmp(value, "raw")?ZMS_RAW:mode;
    //     mode = !strcmp(value, "zip")?ZMS_ZIP:mode;
    //     mode = !strcmp(value, "single")?ZMS_SINGLE:mode;
    //   } else if ( !strcmp(name, "format") ) {
    //     strncpy( format, value, sizeof(format) );
    //   } else if ( !strcmp(name, "monitor") ) {
    //     monitor_id = atoi(value);
    //     if ( source == ZMS_UNKNOWN )
    //       source = ZMS_MONITOR;
    //   } else if ( !strcmp(name, "time") ) {
    //     event_time = atoi(value);
    //   } else if ( !strcmp(name, "event") ) {
    //     event_id = strtoull(value, NULL, 10);
    //     source = ZMS_EVENT;
    //   } else if ( !strcmp(name, "frame") ) {
    //     frame_id = strtoull(value, NULL, 10);
    //     source = ZMS_EVENT;
    //   } else if ( !strcmp(name, "scale") ) {
    //     scale = atoi(value);
    //   } else if ( !strcmp(name, "rate") ) {
    //     rate = atoi(value);
    //   } else if ( !strcmp(name, "maxfps") ) {
    //     maxfps = atof(value);
    //   } else if ( !strcmp(name, "bitrate") ) {
    //     bitrate = atoi(value);
    //   } else if ( !strcmp(name, "ttl") ) {
    //     ttl = atoi(value);
    //   } else if ( !strcmp(name, "replay") ) {
    //     if ( !strcmp(value, "gapless") ) {
    //       replay = EventStream::MODE_ALL_GAPLESS;
    //     } else if ( !strcmp(value, "all") ) {
    //       replay = EventStream::MODE_ALL;
    //     } else if ( !strcmp(value, "none") ) {
    //       replay = EventStream::MODE_NONE;
    //     } else if ( !strcmp(value, "single") ) {
    //       replay = EventStream::MODE_SINGLE;
    //     } else {
    //       Error("Unsupported value %s for replay, defaulting to none", value);
    //     }
    //   } else if ( !strcmp(name, "connkey") ) {
    //     connkey = atoi(value);
    //   } else if ( !strcmp(name, "buffer") ) {
    //     playback_buffer = atoi(value);
    //   } else if ( !strcmp(name, "auth") ) {
    //     strncpy(auth, value, sizeof(auth)-1);
    //   } else if ( !strcmp(name, "token") ) {
    //     jwt_token_str = value;
    //     Debug(1, "ZMS: JWT token found: %s", jwt_token_str.c_str());
    //   } else if ( !strcmp(name, "user") ) {
    //     username = UriDecode(value);
    //   } else if ( !strcmp(name, "pass") ) {
    //     password = UriDecode(value);
    //     Debug(1, "Have %s for password", password.c_str());
    //   } else {
    //     Debug(1, "Unknown parameter passed to zms %s=%s", name, value);
    //   }  // end if possible parameter names
    // } // end foreach parm

    const char *folderPath = "/src/FFmpeg-Test/assets/%i/%05d-capture.jpg";
    const char *videoPath = "/src/FFmpeg-Test/assets/15/15-video.mp4";
    static unsigned char temp_img_buffer[(2048 * 1536) * 4];

    //send file jpg
    // fputs("Content-Type: multipart/x-mixed-replace;boundary=ZoneMinderFrame\r\n\r\n", stdout);
    // int curr_file_id = 1;
    // char filePath[45];
    // static struct stat filestat;
    // FILE *fs;
    // while (1)
    // {
    //     snprintf(filePath, sizeof(filePath), folderPath, eventid, curr_file_id);
    //     fs = fopen(filePath, "rb");
    //     if (!fs)
    //     {
    //         break;
    //     }
    //     fprintf(stdout, "--ZoneMinderFrame\r\n");

    //     int img_buffer_size = 0;
    //     uint8_t *img_buffer = temp_img_buffer;
    //     char buffer;
    //     img_buffer_size = fread(img_buffer, 1, sizeof(temp_img_buffer), fs);
    //     fputs("Content-Type: image/jpeg\r\n", stdout);
    //     fprintf(stdout, "Content-Length: %d\r\n\r\n", (int)img_buffer_size);
    //     fwrite(img_buffer, img_buffer_size, 1, stdout);
    //     fclose(fs);
    //     fputs("\r\n\r\n", stdout);
    //     fflush(stdout);
    //     usleep(100000 / fps);
    //     curr_file_id++;
    // }

    //send frame from file mp4
    fputs("Content-Type: multipart/x-mixed-replace;boundary=ZoneMinderFrame\r\n\r\n", stdout);
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
    outFormatCtx = avformat_alloc_context();

    //init jpeg encoder context
    // const AVCodec *enc = avcodec_find_encoder(AV_CODEC_ID_JPEG2000);
    // if (!enc)
    // {
    //     fprintf(stderr, "Failed to find encoder\n");
    //     return true;
    // }

    // outCodecCtx = avcodec_alloc_context3(enc);
    // if (!outCodecCtx)
    // {
    //     printf("Failed to allocate the codec context\n");
    //     return true;
    // }

    // // The parameters of the video to be encoded
    // // can be modefied as required
    // outCodecCtx->width = inFormatCtx->streams[mVideoStreamIndex]->codecpar->width; //equal to the YUV file size
    // outCodecCtx->height = inFormatCtx->streams[mVideoStreamIndex]->codecpar->height;
    // outCodecCtx->bit_rate = 1000000; // 1Mbps
    // outCodecCtx->gop_size = 10;
    // outCodecCtx->time_base = {1, 24};
    // outCodecCtx->framerate = {24, 1};
    // outCodecCtx->max_b_frames = 1;
    // outCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    // outCodecCtx->pix_fmt = inCodecCtx->pix_fmt;

    // if (avcodec_open2(outCodecCtx, enc, NULL) < 0)
    // {
    //     fputs("Content-Type: text/html\r\n\r\n", stdout);
    //     printf("Failed to open codec\n");
    //     return true;
    // }

    // read frame from video
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    AVStream *pic_stream;
    int tmpW = inFormatCtx->streams[mVideoStreamIndex]->codecpar->width;
    int tmpH = inFormatCtx->streams[mVideoStreamIndex]->codecpar->height;
    int got_pic = 1;

    char outFile[50] = {0};
    sprintf(outFile, "/src/FFmpeg-Test/output/stream.jpg");

    avformat_alloc_output_context2(&outFormatCtx, NULL, NULL, outFile);
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
    // sprintf(outFile, "/src/FFmpeg-Test/output/Sample_%dx%d_yuv420p.yuv", tmpW, tmpH);

    while (av_read_frame(inFormatCtx, &packet) >= 0)
    {
        // fprintf(stdout, "--ZoneMinderFrame\r\n");

        if (packet.stream_index == mVideoStreamIndex)
        {
            avcodec_send_packet(inCodecCtx, &packet);
            int ret = avcodec_receive_frame(inCodecCtx, frame);
            // fputs("Decoded frame\n", stdout);
            if (!ret)
            {
                // uint8_t *buffer = NULL;
                // size_t buffer_size;
                AVPacket *jpg_packet = av_packet_alloc();
                // av_image_fill_arrays(frame->data, frame->linesize, buffer, AV_PIX_FMT_YUV420P, tmpW, tmpH, 1);
                avcodec_send_frame(outCodecCtx, frame);
                int ret = avcodec_receive_packet(outCodecCtx, jpg_packet);
                if (ret == 0)
                {
                    // fputs("Content-Type: image/jpeg\r\n", stdout);
                    // fprintf(stdout, "Content-Length: %d\r\n\r\n", jpg_packet->size);
                    // fwrite(jpg_packet->data, 1, jpg_packet->size, stdout);
                    // fputs("\r\n\r\n", stdout);
                    // fflush(stdout);
                    pic_stream = avformat_new_stream(outFormatCtx, 0);
                    if (pic_stream)
                    {
                        // FILE *fd = fopen(outFile, "wb");
                        // fwrite(jpg_packet->data, 1, jpg_packet->size, fd);
                        // fclose(fd);

                        //Write Header
                        if (avformat_write_header(outFormatCtx, NULL) >= 0)
                        {

                            //Write body
                            av_write_frame(outFormatCtx, jpg_packet);

                            //Write Trailer
                            av_write_trailer(outFormatCtx);
                            // printf("Encoded frame successfully!\n");
                            FILE *stream = fopen(outFile, "rb");
                            int img_buffer_size = 0;
                            uint8_t *img_buffer = temp_img_buffer;
                            img_buffer_size = fread(img_buffer, 1, sizeof(temp_img_buffer), stream);
                            fprintf(stdout, "--ZoneMinderFrame\r\n");
                            fputs("Content-Type: image/jpeg\r\n", stdout);
                            fprintf(stdout, "Content-Length: %d\r\n\r\n", (int)img_buffer_size);
                            fwrite(img_buffer, img_buffer_size, 1, stdout);
                            fclose(stream);
                            fputs("\r\n\r\n", stdout);
                            fflush(stdout);
                        }
                    }
                    got_pic++;
                    // sprintf(outFile, "/src/FFmpeg-Test/output/stream/%05d.jpg", got_pic);
                    // FILE *stream = fopen(outFile, "rb");
                    // int img_buffer_size = 0;
                    // uint8_t *img_buffer = temp_img_buffer;
                    // img_buffer_size = fread(img_buffer, 1, sizeof(temp_img_buffer), stream);
                    // fputs("Content-Type: image/jpeg\r\n", stdout);
                    // fprintf(stdout, "Content-Length: %d\r\n\r\n", (int)img_buffer_size);
                    // fwrite(img_buffer, img_buffer_size, 1, stdout);
                    // fclose(stream);
                    // fputs("\r\n\r\n", stdout);
                    // fflush(stdout);

                    // fputs("Content-Type: text/html\r\n\r\n", stdout);
                    // fprintf(stdout, "Content-Length: %d\r\n\r\n", (int)jpg_packet->size);
                }
                av_packet_unref(jpg_packet);
                // fwrite(frame->data[0], 1, inCodecCtx->width * inCodecCtx->height, fd);
                // fwrite(frame->data[1], 1, inCodecCtx->width * inCodecCtx->height / 4, fd);
                // fwrite(frame->data[2], 1, inCodecCtx->width * inCodecCtx->height / 4, fd);
            }
        }

        av_packet_unref(&packet);
        usleep((int)packet.pts);
        // break;
    }
    // av_frame_free(&frame);
    //End danger
    avcodec_free_context(&inCodecCtx);
    avformat_close_input(&inFormatCtx);
    avcodec_free_context(&outCodecCtx);
    avformat_free_context(outFormatCtx);
    // unlink("/src/FFmpeg-Test/output/stream.jpg");
    // printf("Closed file: %s\n", videoPath);
    // fputs("Content-Type: text/html\r\n\r\n", stdout);
    // printf("Finish saving frame\n");

    return true;
}