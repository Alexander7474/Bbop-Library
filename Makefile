CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGLEW -lGL

all: final

final: main.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f final