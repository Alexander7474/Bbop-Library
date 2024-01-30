CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGLEW -lGL

SRCS = main.cpp shaderClass.cpp VBO.cpp VAO.cpp EBO.cpp 

OBJS = $(SRCS:.cpp=.o)

all: final

final: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f final $(OBJS)
