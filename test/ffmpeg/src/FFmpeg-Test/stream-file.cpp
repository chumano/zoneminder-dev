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

    const char *folderPath = "/src/FFmpeg-Test/assets/%i/%05d-capture.jpg";
    static unsigned char temp_img_buffer[(2048 * 1536) * 4];

    //send file jpg
    fputs("Content-Type: multipart/x-mixed-replace;boundary=ZoneMinderFrame\r\n\r\n", stdout);
    int curr_file_id = 1;
    char filePath[45];
    static struct stat filestat;
    FILE *fs;
    while (1)
    {
        snprintf(filePath, sizeof(filePath), folderPath, eventid, curr_file_id);
        fs = fopen(filePath, "rb");
        if (!fs)
        {
            break;
        }
        fprintf(stdout, "--ZoneMinderFrame\r\n");

        int img_buffer_size = 0;
        uint8_t *img_buffer = temp_img_buffer;
        char buffer;
        img_buffer_size = fread(img_buffer, 1, sizeof(temp_img_buffer), fs);
        fputs("Content-Type: image/jpeg\r\n", stdout);
        fprintf(stdout, "Content-Length: %d\r\n\r\n", (int)img_buffer_size);
        fwrite(img_buffer, img_buffer_size, 1, stdout);
        fclose(fs);
        fputs("\r\n\r\n", stdout);
        fflush(stdout);
        usleep(100000 / fps);
        curr_file_id++;
    }

    return true;
}