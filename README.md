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

## Documentation

pas encore fait ¯\_(ツ)_/¯
