CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGLEW -lGL

SRCS = main.cpp src/BBOP/Graphics/bbopMathClass.cpp src/BBOP/Graphics/bbopGlobal.cpp src/BBOP/Graphics/sceneClass.cpp src/BBOP/Graphics/shaderClass.cpp src/BBOP/Graphics/textureClass.cpp src/BBOP/Graphics/VBO.cpp src/BBOP/Graphics/VAO.cpp src/BBOP/Graphics/EBO.cpp src/BBOP/Graphics/spriteClass.cpp src/BBOP/Graphics/collisionBoxClass.cpp src/BBOP/Graphics/shapeClass.cpp src/BBOP/Performance/benchmark.cpp

OBJS = $(SRCS:.cpp=.o)

all: final

final: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f final $(OBJS)
