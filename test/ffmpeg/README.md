g++ -w test1.cpp -o test1 $(pkg-config --cflags --libs libavformat libswscale)


#####################################
apt install build-essential pkg-config wget

export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

git clone https://github.com/FFmpeg/FFmpeg.git

apt install libx264-dev libmp3lame-dev 

./configure --disable-x86asm --enable-shared --enable-postproc --enable-gpl --enable-libx264 --enable-libx265  --enable-libmp3lame
make
make install

find . -name "*.so*" -type f -exec cp -f {} libs/ \;


git clone https://github.com/lmshao/FFmpeg-Basic.git


#######################################
libs:
    /usr/include    #header
    /usr/lib        #lib.a
    /usr/local/include
    /usr/local/lib
    

find /usr  -name "*avformat.h" -print