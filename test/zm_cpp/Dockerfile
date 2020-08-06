FROM ubuntu:xenial
MAINTAINER Markos Vakondios <mvakondios@gmail.com> Riley Schuit <riley.schuit@gmail.com>

# Resynchronize the package index files
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    apache2 \
    build-essential \
    cmake \
    dh-autoreconf \
    dpatch \
    git \
    libapache2-mod-php \
    libarchive-zip-perl \
    libavcodec-dev \
    libavdevice-dev \
    libavfilter-dev \
    libavformat-dev \
    libavresample-dev \
    libav-tools \
    libavutil-dev \
    libbz2-dev \
    libcurl4-gnutls-dev \
    libdate-manip-perl \
    libdbd-mysql-perl \
    libdbi-perl \
    libdevice-serialport-perl \
    libgcrypt-dev \
    libgnutls-openssl-dev \
    libjpeg-turbo8 \
    libjpeg-turbo8-dev \
    libmime-lite-perl \
    libmime-perl \
    libmp4v2-dev \
    libmysqlclient-dev \
    libnet-sftp-foreign-perl \
    libnetpbm10-dev \
    libpcre3 \
    libpcre3-dev \
    libpolkit-gobject-1-dev \
    libpostproc-dev \
    libssl-dev \
    libswscale-dev \
    libsys-cpu-perl \
    libsys-meminfo-perl \
    libsys-mmap-perl \
    libtheora-dev \
    libtool \
    libv4l-dev \
    libvlc5 \
    libvlccore8 \
    libvlccore-dev \
    libvlc-dev \
    libvorbis-dev \
    libvpx-dev \
    libwww-perl \
    libjson-any-perl \
    libjson-maybexs-perl \
    libnumber-bytes-human-perl \
    libsoap-wsdl-perl \
    libio-socket-multicast-perl \
    libphp-serialization-perl \
    libimage-info-perl \
    liburi-encode-perl \
    libdata-dump-perl \
    libclass-std-fast-perl \
    libdigest-sha-perl \
    libdata-uuid-perl \
    libfile-slurp-perl \
    libcrypt-eksblowfish-perl \
    libdata-entropy-perl \
    perl-modules \
    libx264-dev \
    mysql-client \
    mysql-server \
    php \
    php-cli \
    php-gd \
    php-mysql \
    ssmtp \
    software-properties-common \
    vlc-data \
    yasm \
    zip

RUN apt-get update \
    && rm -rf /var/lib/apt/lists/*

VOLUME [ "/src" ]

# Get the latest master branch and submodule(s)
#RUN git clone --recursive https://github.com/ZoneMinder/ZoneMinder


# Configure mysql
# No longer needed for zm >= 1.32.0
#RUN echo "sql_mode=NO_ENGINE_SUBSTITUTION" >> /etc/mysql/mysql.conf.d/mysqld.cnf

# Expose http port
EXPOSE 80

# Get the entrypoint script and make sure it is executable
ADD ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh

# This is run each time the container is started
ENTRYPOINT ["/entrypoint.sh"]
