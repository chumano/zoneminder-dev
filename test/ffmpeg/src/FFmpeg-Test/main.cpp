#include <fstream>
#include <string>
#include <vector>
#include <errno.h>
#include "Transcoding.h"
#include <stdio.h>
#include <ctime>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
}

using namespace std;

class Video
{

public:
    int start;
    int end;
    tm startdate;
    tm enddate;
    int index;
    void printTimeStamp()
    {
        printf("Video %i start at %s", index, asctime(&startdate));
        printf("Video %i end at %s", index, asctime(&enddate));
    }
    void setStart(string str)
    {
        sscanf(str.c_str(), "%2d/%2d %2d:%2d:%2d", &startdate.tm_mon, &startdate.tm_mday,
               &startdate.tm_hour, &startdate.tm_min, &startdate.tm_sec);
        startdate.tm_year = 2020 - 1900;
    }
    void setEnd(string str)
    {
        sscanf(str.c_str(), "%2d/%2d %2d:%2d:%2d", &enddate.tm_mon, &enddate.tm_mday,
               &enddate.tm_hour, &enddate.tm_min, &enddate.tm_sec);
        enddate.tm_year = 2020 - 1900;
    }
};

int main(int argc, char *argv[])
{
    //Remuxing
    printf("This is a ffmpeg test\n");
    string output = "./output/out.mp4";
    int mStreamNum;
    int *mStreamMap;
    //Init videos timestamp
    Video video[4];
    int starttime = 42;
    int endttime = 43;
    int startIdx = 15;

    for (int i = 0; i < 4; i++)
    {
        video[i].index = startIdx;
        startIdx++;
        video[i].start = starttime;
        starttime++;
        video[i].end = endttime;
        endttime++;
    }
    video[0].setStart("08/21 10:42:45");
    video[0].setEnd("08/21 10:43:42");
    video[1].setStart("08/21 10:43:42");
    video[1].setEnd("08/21 10:44:39");
    video[2].setStart("08/21 10:44:39");
    video[2].setEnd("08/21 10:45:35");
    video[3].setStart("08/21 10:45:35");
    video[3].setEnd("08/21 10:46:33");
    //Time to extract video
    int startExtract = 45;
    int endExtract = 45;
    tm startExtractDate;
    tm endExtractDate;
    sscanf("08/21 10:42:50", "%2d/%2d %2d:%2d:%2d", &startExtractDate.tm_mon, &startExtractDate.tm_mday,
           &startExtractDate.tm_hour, &startExtractDate.tm_min, &startExtractDate.tm_sec);
    sscanf("08/21 10:46:00", "%2d/%2d %2d:%2d:%2d", &endExtractDate.tm_mon, &endExtractDate.tm_mday,
           &endExtractDate.tm_hour, &endExtractDate.tm_min, &endExtractDate.tm_sec);
    startExtractDate.tm_year = endExtractDate.tm_year = 2020 - 1900;
    FILE *outfs = fopen(output.c_str(), "wb");

    if (!outfs)
    {
        fprintf(stderr, "Could not open output file\n");
        return true;
    }

    //Init output context
    AVFormatContext *outFormatCtxt;

    avformat_alloc_output_context2(&outFormatCtxt, NULL, NULL, output.c_str());
    if (!outFormatCtxt)
    {
        printf("Failed to create output context\n");
        return true;
    }

    //Read input videos
    int64_t prev_packet_duration = 0;
    AVFormatContext *inFmtCtx = NULL;
    bool opendOutput = false;
    bool createdNewStream = false;
    time_t extract_start = mktime(&startExtractDate);
    time_t extract_end = mktime(&endExtractDate);
    time_t video_start;
    time_t video_end;
    for (int k = 0; k < 4; k++)
    {
        video_start = mktime(&video[k].startdate);
        video_end = mktime(&video[k].enddate);
        video[k].printTimeStamp();
        // printf("Extract from %s\n", asctime(&startExtractDate));
        // printf("Extract to %s\n", asctime(&endExtractDate));
        // printf("extract_start and video_end diff: %f\n", difftime(extract_start, video_end));
        // printf("extract_end and video_start diff: %f\n", difftime(extract_end, video_start));
        if (difftime(extract_start, video_end) > 0 || difftime(extract_end, video_start) < 0)
        {
            continue;
        }
        string folderName = to_string(video[k].index);
        string path = "./assets/" + folderName + "/" + folderName + "-video.mp4";
        printf("Input file path: %s\n", path.c_str());
        FILE *infs = fopen(path.c_str(), "rb");
        if (!infs)
        {
            fprintf(stderr, "Could not open input file\n");
            return true;
        }
        if (inFmtCtx)
        {
            printf("Input format context already exists!\n");
            return true;
        }
        if (avformat_open_input(&inFmtCtx, path.c_str(), 0, 0) < 0)
        {
            printf("Failed to open input file '%s'", path.c_str());
            return true;
        }

        if (avformat_find_stream_info(inFmtCtx, 0) < 0)
        {
            printf("Failed to retrieve input stream information");
            return true;
        }
        av_dump_format(inFmtCtx, 0, path.c_str(), 0);

        //Set up output format corresponse to input
        // if (!mStreamNum || !mStreamMap)
        // {
        mStreamNum = inFmtCtx->nb_streams;
        mStreamMap = (int *)av_mallocz_array(mStreamNum, sizeof(mStreamMap));
        // }
        if (!mStreamMap)
        {
            return true;
        }

        int stream_index = 0;
        // Map media stream
        printf("Number of streams: %d\n", inFmtCtx->nb_streams);
        for (int i = 0; i < (int)inFmtCtx->nb_streams; i++)
        {

            AVCodecParameters *inCodecPar = inFmtCtx->streams[i]->codecpar;

            // Non-media stream
            if (inCodecPar->codec_type != AVMEDIA_TYPE_AUDIO &&
                inCodecPar->codec_type != AVMEDIA_TYPE_VIDEO &&
                inCodecPar->codec_type != AVMEDIA_TYPE_SUBTITLE)
            {
                mStreamMap[i] = -1;
                continue;
            }

            mStreamMap[i] = stream_index++;

            // Add a new stream to a media file
            if (!createdNewStream)
            {

                AVStream *outStream = avformat_new_stream(outFormatCtxt, NULL);
                if (!outStream)
                {
                    printf("Failed to allocating output stream\n");
                }
                // copy the contents of src to dst
                if (avcodec_parameters_copy(outStream->codecpar, inCodecPar) < 0)
                {
                    printf("Failed to copy codec parameters\n");
                }
                outStream->codecpar->codec_tag = 0;
                createdNewStream = true;
            }
        }
        av_dump_format(outFormatCtxt, 0, output.c_str(), 1);
        //Finish set up output format

        //Danger!! start reading and write packet
        if (!opendOutput)
        {
            AVOutputFormat *ofmt = outFormatCtxt->oformat;
            if (!(ofmt->flags & AVFMT_NOFILE))
            {

                if (avio_open(&outFormatCtxt->pb, output.c_str(), AVIO_FLAG_WRITE) < 0)
                {
                    printf("Failed to open output file '%s'", output.c_str());
                }
            }

            // write header
            if (avformat_write_header(outFormatCtxt, NULL))
            {
                printf("Error occurred when opening output file\n");
            }
            opendOutput = true;
        }
        AVPacket packet;
        int64_t temp_packet_duration = 0;
        int64_t prev_packet_pts = 0;
        printf("Loop time: %i\n", k + 1);
        unsigned int noWrittenFrames = 0;
        unsigned int noIgnoredFrames = 0;
        double video_timer = (double)video_start;
        while (1)
        {
            AVStream *inStream, *outStream;
            int ret = av_read_frame(inFmtCtx, &packet);
            if (ret < 0)
            {
                if (ret == AVERROR_EOF)
                {
                    printf("End of file: %s\n", path.c_str());
                    // printf("temp packet pts: %" PRIu64 "\n", temp_packet_pts);
                    prev_packet_duration += temp_packet_duration;
                    // printf("prev packet pts: %" PRIu64 "\n", prev_packet_pts_end);
                    printf("Written frames: %3d\n", noWrittenFrames);
                    printf("Ignored frames: %3d\n", noIgnoredFrames);
                }
                else
                {
                    printf("Failed to read frame: %i\n", ret);
                }
                av_packet_unref(&packet);
                break;
            }

            inStream = inFmtCtx->streams[packet.stream_index];
            if (packet.stream_index >= mStreamNum || mStreamMap[packet.stream_index] < 0)
            {
                av_packet_unref(&packet);
                continue;
            }

            packet.stream_index = mStreamMap[packet.stream_index];
            outStream = outFormatCtxt->streams[packet.stream_index];

            // copy packet
            packet.pts = av_rescale_q_rnd(packet.pts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX)) + prev_packet_duration;
            packet.dts = av_rescale_q_rnd(packet.dts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX)) + prev_packet_duration;
            packet.duration = av_rescale_q(packet.duration, inStream->time_base, outStream->time_base);
            packet.pos = -1;
            temp_packet_duration = inStream->duration;
            // if (noFrames == 0)
            // {
            //     printf("packet pts: %" PRIu64 "\n", packet.pts);
            //     printf("packet dts: %" PRIu64 "\n", packet.dts);
            //     printf("prev packet pts: %" PRIu64 "\n", prev_packet_pts_end);
            // printf("out time_base: %i/%i\n", outStream->time_base.num, outStream->time_base.den);
            // printf("packet duration: %" PRIu64 "\n", packet.duration);
            // printf("packet duration scaled: %f\n", ((double)packet.duration * (double)outStream->time_base.num / (double)outStream->time_base.den));
            // }

            //check if frame is between extract range
            video_timer += ((double)packet.duration * (double)outStream->time_base.num / (double)outStream->time_base.den);
            // printf("video timer: %f\n", video_timer);
            // printf("start extract: %f\n", (double)extract_start);
            // printf("end extract : %f\n", (double)extract_end);
            if (video_timer < (double)extract_start || video_timer > (double)extract_end)
            {
                // printf("Frame is not between extract range\n");
                noIgnoredFrames += 1;
                av_packet_unref(&packet);
                continue;
            }

            if (av_interleaved_write_frame(outFormatCtxt, &packet) < 0)
            {
                printf("Error muxing packet\n");
                av_packet_unref(&packet);
                break;
            }
            noWrittenFrames += 1;
            av_packet_unref(&packet);
        }

        //End danger

        avformat_close_input(&inFmtCtx);
        inFmtCtx = NULL;
        fclose(infs);
        printf("Closed file: %s\n", path.c_str());
    }
    // write trailer
    if (av_write_trailer(outFormatCtxt) < 0)
    {
        printf("Failed to write trailer\n");
    }
    fclose(outfs);
    avformat_free_context(outFormatCtxt);
    return 0;
    //End Remuxing
}