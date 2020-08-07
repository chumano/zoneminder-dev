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

RUN apt-get update \
    && rm -rf /var/lib/apt/lists/*

VOLUME [ "/src" ]
WORKDIR /src

# Get the entrypoint script and make sure it is executable
ADD ./entrypoint.sh /
RUN chmod 755 /entrypoint.sh

# This is run each time the container is started
ENTRYPOINT ["/entrypoint.sh"]
