CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGLEW -lGL

SRCS = main.cpp src/bbopfunc.cpp src/sceneClass.cpp src/shaderClass.cpp src/textureClass.cpp src/VBO.cpp src/VAO.cpp src/EBO.cpp src/spriteClass.cpp 

OBJS = $(SRCS:.cpp=.o)

all: final

final: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f final $(OBJS)
