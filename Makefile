CC = g++
#comment this if you are on macOS
CFLAGS = -std=c++11 -Wall
LIBS = -lglfw -lGLEW -lGL -lfreetype 

#Uncomment if you use macOS or if you are gay
#CFLAGS = -std=c++11 -Wall -I/opt/homebrew/Cellar/freetype/2.13.2/include/freetype2 -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/usr/local/include/GLFW
#LIBS = -L/opt/homebrew/Cellar/freetype/2.13.2/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -framework Cocoa -framework OpenGL -framework IOKit -lfreetype -lglfw3 -lGLEW.2.2.0

SRCS = src/BBOP/Graphics/bbopFunc.cpp src/BBOP/Graphics/fontsClass.cpp src/BBOP/Graphics/shaders.cpp src/BBOP/Graphics/bbopMathClass.cpp src/BBOP/Graphics/bbopGlobal.cpp src/BBOP/Graphics/sceneClass.cpp src/BBOP/Graphics/cameraClass.cpp src/BBOP/Graphics/shaderClass.cpp src/BBOP/Graphics/textureClass.cpp src/BBOP/Graphics/VBO.cpp src/BBOP/Graphics/VAO.cpp src/BBOP/Graphics/EBO.cpp src/BBOP/Graphics/spriteClass.cpp src/BBOP/Graphics/collisionBoxClass.cpp src/BBOP/Graphics/shapeClass.cpp src/BBOP/Performance/benchmark.cpp src/BBOP/Graphics/lightClass.cpp
SRCSM = main.cpp

OBJS = $(SRCSM:.cpp=.o) $(SRCS:.cpp=.o)
OBJSNM = $(SRCS:.cpp=.o) 

all: final

final: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f final $(OBJS)
	rm -rf /usr/local/shaders

install:
	ar rcs libbbop.a $(OBJSNM)
	cp -r include/BBOP /usr/local/include/
	mv libbbop.a /usr/local/lib/

uninstall:
	rm /usr/local/lib/libbbop.a
	rm -rf /usr/local/include/BBOP

update:
	make clean
	make
	sudo make install
