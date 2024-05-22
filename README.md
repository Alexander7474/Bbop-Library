# Bbop Library

![GitHub License](https://img.shields.io/github/license/Alexander7474/Bbop-Library)
![GitHub Release](https://img.shields.io/github/v/release/Alexander7474/Bbop-Library?include_prereleases&color=pink)
![GitHub commits since latest release](https://img.shields.io/github/commits-since/Alexander7474/Bbop-Library/latest?color=green)
![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/t/Alexander7474/Bbop-Library/main)
![GitHub last commit](https://img.shields.io/github/last-commit/Alexander7474/Bbop-Library?link=https%3A%2F%2Fgithub.com%2FAlexander7474%2FBbop-Library%2Fcommits%2Fmain%2F)
![GitHub top language](https://img.shields.io/github/languages/top/Alexander7474/Bbop-Library?logo=c%2B%2B&logoColor=red&color=red)

Bbop est un projet de librairie graphique utilisant l'api opengl ( :point_right: bientôt sous vulkan :point_left: ).   
La librairie permet de créer des jeux vidéos 2D ou des applications de bureau. Elle embarque un grand nombre d'objets en pasant par des formes géométriques et aux sprites jusqu'à la gestions de l'éclairages et des effets de lumières.   
Elle est principalement développée et maintenue sous linux et macOS ( je fais tous mon possible pour une sortie sur window ).   

# Naviguer

[![Installation](https://img.shields.io/badge/Installation-lightgreen?style=for-the-badge)](#installation)   
[![Static Badge](https://img.shields.io/badge/Documentation-lightblue?style=for-the-badge)](https://alexander7474.github.io/bbop-web-docs/)   
[![Static Badge](https://img.shields.io/badge/Exemple_code-lightyellow?style=for-the-badge)](https://alexander7474.github.io/bbop-web-docs/)   
[![Static Badge](https://img.shields.io/badge/Report_Bug-red?style=for-the-badge&logoColor=red)](#report-bug)   
[![Static Badge](https://img.shields.io/badge/Support-purple?style=for-the-badge)](#supporting)   
[![Static Badge](https://img.shields.io/badge/Contributors-yellow?style=for-the-badge)](#contributors)   

# Installation  

## Librairies externes nécessaires

### ![Static Badge](https://img.shields.io/badge/Debian-Packages-grey?style=for-the-badge&logo=debian&labelColor=D70A53)

```
sudo apt-get install libglew-dev libglfw3-dev xorg-dev libfreetype6-dev libstb-dev 
```

### ![Static Badge](https://img.shields.io/badge/Arch_Linux-Packages-grey?style=for-the-badge&logo=arch-linux&logoColor=fff&labelColor=1793D1) 

(I use arch btw)

```
sudo pacman -S glew glfw stb freetype2 glm
```

### ![Static Badge](https://img.shields.io/badge/mac_os-Packages-grey?style=for-the-badge&logo=macos&logoColor=F0F0F0&labelColor=black)

```
brew install glew freetype glfw glm
```

### :warning: Issue avec glfw et glm :warning:

Dans certain cas il est nécessaires d'installer glfw et glm en les compilants depuis leurs repo github.

## Compiler et installer bbop

### ![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
```
git clone https://github.com/Alexander7474/Bbop-Library.git
cd Bbop-Library
make && sudo make install
```

### ![macOS](https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=macos&logoColor=F0F0F0)

```
git clone https://github.com/Alexander7474/Bbop-Library.git
cd Bbop-Library
```

Avant d'utiliser make pour compiler et installer bbop sur macOS il faut modifier le makefile selon commentaires de celui ci.

```
make && sudo make install
```

## Compiler un projet

### ![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

```
g++ -I/usr/include/freetype2 -c main.cpp -o main.o
g++ main.o -o final -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype
```

### ![macOS](https://img.shields.io/badge/mac%20os-000000?style=for-the-badge&logo=macos&logoColor=F0F0F0)

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
