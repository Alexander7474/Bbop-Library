# Bbop Library
## Informations
Bbop est un projet de library graphique utilisant opengl. La lib permet de gérer plus que de simple forme géométrique comme l'éclairage d'une scène, des points de lumières ou encore des ombrages.
Auteur: Alexandre L
Versions: 0.1
# Installation  
## Installer les lib nécessaires: 
```
sudo apt-get install libglew-dev libglfw3-dev xorg-dev
sudo apt-get install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules libstb-dev
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
## Compiler et installer bbop
### !!! Attention a bien avoir installer les libs necessaires !!!
```
git clone https://github.com/Alexander7474/BibibopEngine.git Bibibop
cd Bibibop
make && sudo make install
```
# Documentation

pas encore fait ¯\_(ツ)_/¯
