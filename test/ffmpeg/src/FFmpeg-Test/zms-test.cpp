#include <stdio.h>
#include <cstdlib>
#include <sys/stat.h>
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <unistd.h>

using namespace std;

const string ENV[24] = {
    "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE", "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING", "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION", "HTTP_HOST", "HTTP_USER_AGENT", "PATH", "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT", "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME", "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN", "SERVER_NAME", "SERVER_PORT", "SERVER_PROTOCOL", "SERVER_SIGNATURE", "SERVER_SOFTWARE"};

int main(int argc, char *argv[])
{
    double fps = 2.0;

    const char *query = getenv("QUERY_STRING");
    char temp_query[1024];
    strncpy(temp_query, query, sizeof(temp_query) - 1);
    char *q_ptr = temp_query;
    char *parms[16]; // Shouldn't be more than this
    int parm_no = 0;
    while ((parm_no < 16) && (parms[parm_no] = strtok(q_ptr, "&")))
    {
        parm_no++;
        q_ptr = NULL;
    }

    for (int p = 0; p < parm_no; p++)
    {
        char *name = strtok(parms[p], "=");
        char const *value = strtok(NULL, "=");
        if (!value)
            value = "";
        if (!strcmp(name, "fps"))
        {
            fps = atof(value);
        }
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
    } // end foreach parm

    fputs("Content-Type: multipart/x-mixed-replace;boundary=ZoneMinderFrame\r\n\r\n", stdout);
    const char *folderPath = "/src/FFmpeg-Test/assets/%i/%05d-capture.jpg";
    for (int i = 15; i < 17; i++)
    {
        int curr_file_id = 1;
        char filePath[45];
        static struct stat filestat;
        FILE *fs;
        while (1)
        {
            snprintf(filePath, sizeof(filePath), folderPath, i, curr_file_id);
            fs = fopen(filePath, "rb");
            if (!fs)
            {
                break;
            }
            fprintf(stdout, "--ZoneMinderFrame\r\n");
            static unsigned char temp_img_buffer[(2048 * 1536) * 4];
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
    }
    return true;
}