.PHONY:build
build:
			g++ -O2 src/main.cpp src/streamer.cpp src/text_handler.cpp -o freq

.DEFAULT_GOAL := build
