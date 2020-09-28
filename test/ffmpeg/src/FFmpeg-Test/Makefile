all: main.cpp Transcoding.cpp
	g++ main.cpp Transcoding.cpp -o main -lavformat -lavcodec -lavutil -lavfilter

test: zms-test.cpp
	g++ zms-test.cpp -o ./cgi/test