# ZoneMinder Development Dockerfiles
This folder contains Docker files used for running the latest code from the ZoneMinder master branch.
These are not intended for production. See the [release](https://github.com/ZoneMinder/zmdockerfiles/tree/master/release) folder if you are looking to run ZoneMinder inside Docker for production.

Contributions are welcome, but please follow these simple guidelines:

- Only one Dockerfile per distro
- Keep each Dockerfile sorted by distro
- Use our [entrypoint script](https://github.com/ZoneMinder/zmdockerfiles/blob/master/utils/entrypoint.sh) as the entrypoint in your Dockerfile. It is intended to work with most Linux distros and will take care of starting mysql, apache, then zoneminder.
- Each Dockerfile should be self sufficient. It should grab the ZoneMinder project, and any other other requried files, from github or other online resource, rather than expect files to pre-exist on the filesystem.


docker build . -t zmdev

docker run -d -t -p 1080:80  --shm-size="512m" --name  zmdev zmdev 
- ========================================
git clone --recursive https://github.com/chumano/zoneminder


./CMakeLists.txt
./db/CMakeLists.txt
./distros/opensuse/CMakeLists.txt
./distros/redhat/CMakeLists.txt
./misc/CMakeLists.txt
./onvif/CMakeLists.txt
./onvif/modules/CMakeLists.txt
./onvif/proxy/CMakeLists.txt
./scripts/CMakeLists.txt
./scripts/ZoneMinder/CMakeLists.txt
./src/CMakeLists.txt
./src/libbcrypt/CMakeLists.txt
./web/CMakeLists.txt
./web/api/CMakeLists.txt
./web/tools/mootools/CMakeLists.txt