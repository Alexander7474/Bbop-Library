g++ -c main.cpp src/Player.cpp
g++ main.o Player.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
./sfml-app
rm *.o sfml-app