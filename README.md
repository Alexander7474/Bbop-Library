# Bbop Library
## Informations

![GitHub License](https://img.shields.io/github/license/Alexander7474/Bbop-Library)
![GitHub Release](https://img.shields.io/github/v/release/Alexander7474/Bbop-Library?include_prereleases&color=pink)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/Alexander7474/Bbop-Library/latest?color=green)
![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/t/Alexander7474/Bbop-Library/main)
![GitHub last commit](https://img.shields.io/github/last-commit/Alexander7474/Bbop-Library?link=https%3A%2F%2Fgithub.com%2FAlexander7474%2FBbop-Library%2Fcommits%2Fmain%2F)
![GitHub top language](https://img.shields.io/github/languages/top/Alexander7474/Bbop-Library?logo=c%2B%2B&logoColor=red&color=red)

Bbop est un projet de library graphique utilisant opengl. La lib permet de gérer plus que de simple forme géométrique comme l'éclairage d'une scène, des points de lumières ou encore des ombrages.

1. [![Installation](https://img.shields.io/badge/Installation-lightgreen?style=for-the-badge)](#installation)
2. [![Static Badge](https://img.shields.io/badge/Documentation-lightblue?style=for-the-badge)](https://alexander7474.github.io/bbop-web-docs/)
3. [![Static Badge](https://img.shields.io/badge/Report_Bug-red?style=for-the-badge&logoColor=red)](#report-bug)
4. [![Static Badge](https://img.shields.io/badge/Support-purple?style=for-the-badge)](#supporting)
5. [![Static Badge](https://img.shields.io/badge/Contributors-yellow?style=for-the-badge)](#contributors)

# Installation  
## Installer les lib nécessaires: 
[![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)](https://www.opengl.org)
### Linux Packages
```
sudo apt-get install libglew-dev libglfw3-dev xorg-dev libfreetype6-dev
sudo apt-get install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules libstb-dev 
```
### MacOS Packages
```
brew install glew freetype 
```
### Installer glfw:
on clone le repo glfw
```
git clone https://github.com/glfw/glfw.git
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
git clone https://github.com/g-truc/glm.git
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
### Linux
```
git clone https://github.com/Alexander7474/Bbop-Library.git
cd Bbop-Library
make && sudo make install
```
### MacOS
```
git clone https://github.com/Alexander7474/Bbop-Library.git
cd Bbop-Library
```
Avant d'utiliser make pour compiler et installer bbop sur macOS il faut modifier le makefile selon commentaires de celui ci.
```
make && sudo make install
```
## Compiler un projet
### Linux
```
g++ -I/usr/include/freetype2 -c main.cpp -o main.o
g++ main.o -o final -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype
```
### MacOS
```
g++ -I/opt/homebrew/Cellar/freetype/2.13.2/include/freetype2 -I/opt/homebrew/Cellar/glew/2.2.0_1/include -I/usr/local/include/GLFW -c main.cpp -o main.o
g++ main.o -o final -std=c++11 -Wall -lbbop -L/opt/homebrew/Cellar/freetype/2.13.2/lib -L/opt/homebrew/Cellar/glew/2.2.0_1/lib -framework Cocoa -framework OpenGL -framework IOKit -lfreetype  -lglfw3 -lGLEW.2.2.0
```

# Exemple
```
int main()
{
    //creation de la fenêtre glfw
    GLFWwindow * window;
    //initialisation de la lib
    bbopInit(1920,1080,"window name",window);
    //main while loop
    while (!glfwWindowShouldClose(window))
    {
      // clear de la fenêtre en noire
      bbopCleanWindow(window,Vector3i(0,0,0),1.0f));
    
      ///////////////
      // ton code ici
      ///////////////
    
      // vérification des erreurs
      bbopErrorCheck();
      // swap du back buffer avec le front buffer
      glfwSwapBuffer(window);
      // recupération des events glfw
      glfwPollEvents();
    }
    // destruction de la fen^tre et fin de glfw
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

# Report Bug

Merci d'avance de votre contribution au projet.

[![Static Badge](https://img.shields.io/badge/Report_issue-github-black?style=for-the-badge&logo=github)](https://github.com/Alexander7474/Bbop-Library/issues)

# Supporting

La librairie est libre de droit, merci d'avance de votre soutien.

[![Static Badge](https://img.shields.io/badge/Sponsor_on_github-Alexander7474-pink?style=for-the-badge&logo=githubsponsors)](https://github.com/sponsors/Alexander7474)

# Contributors

[![Static Badge](https://img.shields.io/badge/Je_suis_seule-Alexander7474-red?style=for-the-badge&logoColor=red)](https://github.com/Alexander7474)
