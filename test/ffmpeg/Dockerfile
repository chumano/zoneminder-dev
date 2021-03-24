FROM ubuntu:bionic

# Resynchronize the package index files
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    git \
    zip \ 
    build-essential \
    pkg-config \
    wget \
    ffmpeg

RUN apt-get install unzip

RUN apt-get update \
    && rm -rf /var/lib/apt/lists/*

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update \
    && apt-get install -y apache2 php libapache2-mod-php \
    && service apache2 restart

# Copy ffmpeg libs
#ADD ./ffmpeglibs/include/ /usr/local/include/
#ADD ./ffmpeglibs/lib/ /usr/local/lib/
ADD ./ffmpeglibs.zip /tmp/
RUN unzip /tmp/ffmpeglibs.zip -d /tmp
RUN cp -r /tmp/ffmpeglibs/include/ /usr/local/
RUN cp -r /tmp/ffmpeglibs/lib/ /usr/local/

# create symlink
WORKDIR /usr/local/lib/
RUN ln -s libavcodec.so.58.99.100 libavcodec.so \
    && ln -s libavdevice.so.58.11.101 libavdevice.so \
    && ln -s libavfilter.so.7.87.100 libavfilter.so \
    && ln -s libavformat.so.58.49.100 libavformat.so \
    && ln -s libavutil.so.56.58.100 libavutil.so \
    && ln -s libpostproc.so.55.8.100 libpostproc.so \
    && ln -s libswresample.so.3.8.100 libswresample.so \
    && ln -s libswscale.so.5.8.100 libswscale.so \
    #
    && ln -s libavcodec.so.58.99.100 libavcodec.so.58 \
    && ln -s libavdevice.so.58.11.101 libavdevice.so.58 \
    && ln -s libavfilter.so.7.87.100 libavfilter.so.7 \
    && ln -s libavformat.so.58.49.100 libavformat.so.58 \
    && ln -s libavutil.so.56.58.100 libavutil.so.56 \
    && ln -s libpostproc.so.55.8.100 libpostproc.so.55 \
    && ln -s libswresample.so.3.8.100 libswresample.so.3 \
    && ln -s libswscale.so.5.8.100 libswscale.so.5

RUN echo 'export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH' >> ~/.bashrc

VOLUME [ "/src" ]
WORKDIR /src

# Get the entrypoint script and make sure it is executable
ADD ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh

# This is run each time the container is started
ENTRYPOINT ["/entrypoint.sh"]
