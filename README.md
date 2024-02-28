# Bbop Library
## Informations

[![Version 0.1](lien_vers_image_badge)](https://github.com/Alexander7474/Bbop-Library/releases/tag/apha)
[![Release](lien_vers_image_badge)](https://github.com/Alexander7474/Bbop-Library/releases)

Bbop est un projet de library graphique utilisant opengl. La lib permet de gérer plus que de simple forme géométrique comme l'éclairage d'une scène, des points de lumières ou encore des ombrages.
Auteur: Alexandre L
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

## Init et autre

### bbopInit(int windowX, int windowY, const char* windowName, GLFW*& window)
Initialise opengl et bbop pour pouvoir utiliser la lib.
Prend en paramètre la taille de la fenêtre, son nom et la fenêtre glfw à utiliser comme contexte opengl.

### bbopCleanWindow(Vector3i rgb, float alpha)
Nettoie la fenêtre avant un nouvelle affichage
Prend en paramètre la couleur de fond et la transparence de la fenêtre.

### bbopErrorCheck()
Vérifie le cache d'erreur opengl et affiche des possibles erreurs

#### Exemple
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
      bbopCleanWindow(Vector3i(0,0,0),1.0f));
    
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

## Vector~~

### Vector2i(int x, int y) Vector2f(float x, float y) Vector2d(double x, double y)
Prend en paramètre x et y et permet de gèrer des paire. (Position, vecteur de vitesse, ext...).
x et y ne sont pas privé.
#### Exemple
```
Vector2f vector(120.0f, 564.2f);
std::cout << vector.x << ";" << vector.y << std::endl;
```

### Vector3i(int x, int y, intz) Vector3f(float x, float y, float z) Vector3d(double x, doule y, double z)
Même chose que pour le Vector2~ mais pour des paires de 3 comme rgb.

## Scene

### <span style="color:blue">Scene()</span>
Permet de gérer l'éclairage gloabal, le shader utilisé, les variables uniform de shader et l'affichage de n'importe quelles forme/sprite/texte.
La class n'est pas encore finalisé est ne permet pas encore une gestion complète de l'éclairage.
#### Exemple d'utilisation
```
// creation d'une scène
Scene defaultScene;
// creation d'un rectangle
RectangleShape rectangle;
// affichage du rectangle
defaultScene.Draw(rectangle);
```
