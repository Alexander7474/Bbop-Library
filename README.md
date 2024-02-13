# Bibibop engine

## Lancer le projet
### Compilation:
Make dans le dossier racine du projet
```
make
```
### Execution:
```
./final
```

## Installation environement dev 
### Installer les lib nécessaires: 
```
sudo apt-get install libglew-dev libglfw3-dev xorg-dev
sudo apt-get install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules
```
### Installer glfw: 
on clone le repo glfw
```
git clone https://github.com/glfw/glfw.github
cd glfw
```
Création du dossier de build
```
mkdir build
cd build
```
Cmake avec le projet
```
cmake ..
```
Installation de glfw
```
make && sudo make install
```
### Installer glm
on clone le repo glm
```
git clone https://github.com/glfw/glfw.git
cd glm
```
Cmake avec le projet
```
cmake \
    -DGLM_BUILD_TESTS=OFF \
    -DBUILD_SHARED_LIBS=OFF \
    -B build .
cmake --build build -- all
cmake --build build -- install
```
## Documentation

pas encore fait ¯\_(ツ)_/¯
