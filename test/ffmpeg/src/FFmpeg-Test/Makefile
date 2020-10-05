all: main.cpp Transcoding.cpp
	g++ main.cpp Transcoding.cpp -o main -lavformat -lavcodec -lavutil -lavfilter

test: zms-test.cpp
	g++ zms-test.cpp -o ./cgi/test
	
frame: zms-test.cpp
	g++ zms-test.cpp -o ./cgi/frame -lavformat -lavcodec -lavutil -lavfilter
	
stream-file: stream-file.cpp
	g++ stream-file.cpp -o ./cgi/stream-file -lavformat -lavcodec -lavutil -lavfilter
	
stream-frame: stream-frame.cpp
	g++ stream-frame.cpp -o ./cgi/stream-frame -lavformat -lavcodec -lavutil -lavfilter