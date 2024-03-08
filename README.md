# Bbop Library
## Informations

[![Last version](https://img.shields.io/badge/Last_version-0.1-blue)](https://github.com/Alexander7474/Bbop-Library/releases)
[![License](https://img.shields.io/badge/License-GPL-&#45;3.0-blue)](https://github.com/Alexander7474)
![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/t/Alexander7474/Bbop-Library/main)
![GitHub last commit](https://img.shields.io/github/last-commit/Alexander7474/Bbop-Library?link=https%3A%2F%2Fgithub.com%2FAlexander7474%2FBbop-Library%2Fcommits%2Fmain%2F)
![GitHub top language](https://img.shields.io/github/languages/top/Alexander7474/Bbop-Library?logo=c%2B%2B&logoColor=red&color=red)

Bbop est un projet de library graphique utilisant opengl. La lib permet de gérer plus que de simple forme géométrique comme l'éclairage d'une scène, des points de lumières ou encore des ombrages.

1. [![Installation](https://img.shields.io/badge/Installation-lightgreen?style=for-the-badge)](#installation)
2. [![Static Badge](https://img.shields.io/badge/Documentation-lightblue?style=for-the-badge)](#documentation)
3. [![Static Badge](https://img.shields.io/badge/Report_Bug-red?style=for-the-badge&logoColor=red)](#report-bug)
4. [![Static Badge](https://img.shields.io/badge/Support-purple?style=for-the-badge)](#supporting)
5. [![Static Badge](https://img.shields.io/badge/Contributors-yellow?style=for-the-badge)](#contributors)

# Installation  
## Installer les lib nécessaires: 
[![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)](https://www.opengl.org)
```
sudo apt-get install libglew-dev libglfw3-dev xorg-dev libfreetype6-dev
sudo apt-get install libwayland-dev libxkbcommon-dev wayland-protocols extra-cmake-modules libstb-dev 
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
### !!! Attention a bien avoir installer les libs necessaires !!!
```
git clone https://github.com/Alexander7474/BibibopEngine.git Bibibop
cd Bibibop
make && sudo make install
```
### compiler et lancer un projet
```
g++ -I/usr/include/freetype2 -c main.cpp -o main.o
g++ main.o -o final -std=c++11 -Wall -lbbop -lGLEW -lGL -lglfw -lfreetype
```
# Documentation

1. [Initialisation](#init-et-autre)
2. [Vector](#vector)
3. [Scene](#scene)
4. [Shape](#shape)
5. [RectangleShape](#rectangleshape)
6. [ConvexShape](#convexshape)
7. [CircleShape](#circleshape)
8. [Sprite](#sprite)
9. [TexteBox](#textebox)
10. [CollisionBox](#collisionbox)
11. [Texture](#texture)
12. [Camera](#camera)

## Init et autre 
[Go back](#documentation)

### int bbopInit(int windowX, int windowY, const char* windowName, GLFW*& window)
Initialise opengl et bbop pour pouvoir utiliser la lib.
Param:  
  &nbsp;&nbsp;windowX,windowY: Taille de la fenêtre.  
  &nbsp;&nbsp;windowName: Nom de la fenêtre.  
  &nbsp;&nbsp;window: Fenêtre glfw à utiliser comme contexte opengl.  

### void bbopCleanWindow(GLFWwindow*& window, Vector3i rgb, float alpha)
Nettoie la fenêtre avant un nouvelle affichage
Param:   
  &nbsp;&nbsp;window: fnêtre glfw à clean.   
  &nbsp;&nbsp;rgb: Couleur de fond de la fenêtre.  
  &nbsp;&nbsp;alpha: Transparence du nettoyage(si en dessous de 1,on pourra encore voire les ancien objet sur chaque frame).  

### void bbopErrorCheck()
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

## Vector~~
[Go back](#documentation)
La librairie bbop utilise toujours des vector pour transferer et utiliser n'importe quelle paire ou triplet de int, float ou double.

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
[Go back](#documentation)
Permet de gérer l'éclairage gloabal, le shader utilisé, les variables uniform de shader et l'affichage de n'importe quelles forme/sprite/texte.

### Scene()
Constructeur par défault de scene qui eclaire la scène avec une lumière blanche.

### Scene(float nAmbiantLightValue, Vector3i nAmbiantLightColor)
Constructeur de scène  
Param:  
    &nbsp;&nbsp;nAmbiantLightValue: puissance de l'éclairage de la scène.  
    &nbsp;&nbsp;nAbiantLightColor: couleur de l'éclairage de la scène.  

### void Use()
Permet de spécifier la scène à utiliser  

### void setAmbiantLightValue(float nAmbiantLightValue)
Change la puissance de l'éclairage d'une scène.  
Param:  
    &nbsp;&nbsp;nAmbiantLightValue: puissance de l'éclairage.  

### void getAmbiantLightValue()
Return:   
    &nbsp;&nbsp;ambiantLightValue: puissance de l'éclairage de la scène  

### void setAmbiantLightColor(float nAmbiantLightColor)
Change la couleur de l'éclairage d'une scène.  
Param:  
    &nbsp;&nbsp;nAmbiantLightColor: couleur de l'éclairage.  

### void getAmbiantLightColor()
Return:   
    &nbsp;&nbsp;ambiantLightColor: couleur de l'éclairage de la scène.  

### void Draw(BbopDrawable& spr)
Dessine avec les paramètres de scène l'objet passé en paramètre.  
Param:  
    &nbsp;&nbsp;spr: objet BbopDrawble à dessiner.  

#### Exemple d'utilisation
```
// creation d'une scène
Scene defaultScene;
// creation d'un rectangle
RectangleShape rectangle;
// affichage du rectangle
defaultScene.Draw(rectangle);
```

## Shape
[Go back](#documentation)
La plus part des objets dessinables de la librairie hérite de cette classe, elle permet de gérer leur taille, position, origine, rotation, couleur, collision et transparence. Cette class hérite aussi de BbopDrawable et tous ces enfants peuvent êtres dessinés dans une scène.  

### Vector2f getSize()
Return:  
    &nbsp;&nbsp;size: taille de la shape.  

### void setSize(Vector2f nSize)
Change la taille de la shape.  
Param:  
    &nbsp;&nbsp;nSize: taille de la shape.  

### Vector2f getPosition()
Return:  
    &nbsp;&nbsp;pos: position de la shape  

### void setPosition(Vector2f nPos)
Change la position de la shape.  
Param:  
    &nbsp;&nbsp;nPos: position de la shape.

### void move(Vector2f vecM)
Shape peut aussi changer de position en lui appliquant un vecteur de mouvement
Param:  
     &nbsp;&nbsp;vecM: Vecteur de mouvement appliquer à la position de shape.

### Vector2f getOrigin()
Return:  
    &nbsp;&nbsp;nOrigin: origin de la shape.  

### void setOrigin()
Change l'origin de la shape.  
Param:  
    &nbsp;&nbsp;nOrigin: origin dela shape.  

### Vector3i getColor();
Return:  
    &nbsp;&nbsp;RGB: couleur de la shape.  

### void setColor(Vector3i nRGB)
Change la couleur de la shape.  
Param:  
    &nbsp;&nbsp;nRGB: couleur de la shape.  

### float getAlpha();
Return:  
    &nbsp;&nbsp;alpha: transparence de la shape.  

### void setAlpha(float nAlpha)
Change la transparence de la shape.  
Param:    
    &nbsp;&nbsp;nAlpha: transparence de la shape.  

### float getRotation();
Return:  
    &nbsp;&nbsp;rotation: angle de rotation de la shape en radian.  

### void setRotation(float nRotation)
Change la rotation de la shape.   
Param:  
    &nbsp;&nbsp;nRotation: angle de rotation de la shape en radian.  

### CollisionBox* getCollisionBox()
Renvoie la box de collision de la shape pour la modifier ou la comparer a d'autre box(A savoir que collsionBox possède les même méthode que shape pour changer de taille, d'origine et de position).  
Return:  
    &nbsp;&nbsp;shapeCollisionBox: boîte de collision de la shape.  

### void setAutoUpdateCollision(bool etat) 
Change la mise à jour auto de la boîte de collision en fonctio de la shape, cela permet d'avior une boîte de collision avec des propriétées différentes de la shape et personnaliées.   
Param:  
    &nbsp;&nbsp;etat: état de la mise a jour auto (true activé et false désactivé)  

## RectangleShape
[Go back](#documentation)
Gére une forme rectangulaire, hérite de Shape.   
Tous les aspects du rectangle étant déjà gérer par Shape, cette class n'a pas besoin de documentation spécifique.

### RectangleShape()
Constructeur par défault de rectangleShape.  
Le rectangle est en position 0;0, est blanc et fais une taille de 50px*50px

## ConvexShape
[Go back](#documentation)
Gére une forme convex, hérite de Shape.   
**Cette class ne gère pas sa taille de la même manière que rectangle shape. Son attribue size représente la proportion de ces coordonnées dans la fenêtre.
A 1.0;1.0, 1px dans les coordonées de la convex vaut 1px dans la fenêtre.**

### ConvexShape(int nnPoint, Vector2f* nlistPoint)
Contructeur de ConvexShape.  
Créer une forme convex a partir d'une liste de point x;y.  
Param:  
    &nbsp;&nbsp;nnPoint: Nombre de point dans nlistPoint.  
    &nbsp;&nbsp;nlistPoint: List de point où le premier point est toujours utiliser comment centre pour créer la convex.  

### ConvexShape()
Constructeur par défault de ConvexShape.  
Créer une convex sans paramètre. La convex doit tous de même être initialiser avant d'être Draw() avec initConvex().  

### initConvex(int nnPoint, Vector2f* nlistPoint)
Initialise les convex créé avec le constructeur par défault, fonctionne de la même manière que le premier constructeur de ConvexShape.  

## CircleShape
[Go back](#documentation)
Gére une forme circulaire, hérite de ConvexShape(c'est juste un class pour gérer une convex comme un cercle ou un triangle).   

### CircleShape(int nnPoint, float nRadius)
Contructeur de de CircleShape.  
Créer une forme circulaire a partir de sont nombre de point et de saon rayon, peut aussi créer un triangle si on utilise 3 points.  
Param:  
    &nbsp;&nbsp;nnPoint: Nombre de point.  
    &nbsp;&nbsp;nRadius: Rayon du cercle.

### float getRadius()
Return:  
  &nbsp;&nbsp;radius: Rayon de l'objet.  

### void setRadius(float nRadius)
Change le rayon de CircleShape.  
Param:  
  &nbsp;&nbsp;nRadius: Nouveau rayon de l'objet.  

### int getNPointCircle()
Return:  
  &nbsp;&nbsp;nPointCircle: Nombre de point de l'objet.  

### void setNPointCircle(int nnPoint)
Change le nombre de point de CircleShape.  
Param:  
  &nbsp;&nbsp;nnPoint: Nouveau nombre de point de l'objet.  

## Sprite
[Go back](#documentation)
Gère un sprite, hérite de Shape.  
**Cette class ne gère pas sa couleur comme les autres shape, son attribue rgb est un filtre qui s'applique à la texture du sprite si l'option est active.**

### Sprite(Texture nTexture)
Constructeur de sprite avec la texture à attribuer.
Param:
    &nbsp;&nbsp;nTexture: Texture du sprite.

### Sprite()
Constructeur par défault de sprite, la texture dois être associé avant de draw sinon des erreur de pointeur peuvent arriver.

### setTexture(Texture nTexture)
Associe une texture avec le sprite.  
Param:  
    &nbsp;&nbsp;nTexture: Texture du sprite.

### bool getRGBFilterState()
Return:   
    &nbsp;&nbsp;isRGBFilter: true si le filtre rgb est actif et false si non.  

### void setRGBFilterState(bool etat)
Active ou désactive le filtre rgb.  
Param:  
    &nbsp;&nbsp;etat: true si le filtre rgb est actif et false si non.  

## TexteBox
[Go back](#documentation)
Gère une boîte de dialogue, hérite de BbopDrawable.  
**Cette class n'hérite pas de shape mais possède exactement les même fonction pourgérer sa position, son origine, sa couleur, sa transprence et son angle de rotation. Ces méthodes ne seront pas réexpliqué dans cette section**  

### TexteBox(const char * nTexte, int glyphSize, const char* ttfPath)
Constructeur de la class TexteBox.  
Param:  
    &nbsp;&nbsp;nTexte: Texte à afficher avec la class.  
    &nbsp;&nbsp;glyphSize: Taille des caractères.  
    &nbsp;&nbsp;ttfPath: Chemin d'accès vers la police d'écriture en .ttf.  

### const char* getTexte()
Return:  
    &nbsp;&nbsp;texte: Texte affiché par la class.

### void setTexte(const char* nTexte)
Change le texte affiché par la class.  
Param:  
    &nbsp;&nbsp;nTexte: Nouveau texte a afficher.

## CollisionBox
[Go back](#documentation)
Gère une boîte de collision.  
**Cette class n'hérite pas de shape mais possède exactement les même fonction pourgérer sa position, son origine, et sa taille. Ces méthodes ne seront pas réexpliqué dans cette section** 

### CollisionBox(Vector2f nPos, Vector2f nOrigin, Vector2f nSize)
Constructeur de CollisionBox.  
Param:  
    &nbsp;&nbsp;nPos: Position de la box.  
    &nbsp;&nbsp;nOrigin: Origin de la box.  
    &nbsp;&nbsp;nSize: Taille de la box.  

### bool check(CollisionBox *box)
Vérifie si deux box sont en collision.  
Param:  
    &nbsp;&nbsp;box: Boîte à comparer avec la boîte qui appelle la méthode.  
Return:  
    &nbsp;&nbsp;bool: true si les boîtes sont en collision et false si non.  

## Texture
[Go back](#documentation)
Gère une texture. Cette texture peut ensuite être utilisé avec un sprite ou un autre objet qui demande une texture.  

## Camera
[Go back](#documentation)
Gère une camera qui peut utilisé par une Scene pour Draw.

### Texture(const char* textureFileName)
Cosntructeur de la class Texture.  
Param:  
    &nbsp;&nbsp;textureFileName: Chemin d'accès de la texture en .png.  

# Report Bug

Merci d'avance de votre contribution au projet.

[![Static Badge](https://img.shields.io/badge/Report_issue-github-black?style=for-the-badge&logo=github)](https://github.com/Alexander7474/Bbop-Library/issues)

# Supporting

La librairie est libre de droit, merci d'avance de votre soutien.

[![Static Badge](https://img.shields.io/badge/Sponsor_on_github-Alexander7474-pink?style=for-the-badge&logo=githubsponsors)](https://github.com/sponsors/Alexander7474)

# Contributors

[![Static Badge](https://img.shields.io/badge/Je_suis_seule-Alexander7474-red?style=for-the-badge&logoColor=red)](https://github.com/Alexander7474)
