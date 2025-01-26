
# Tuto 

## Mise en place 

Premier programme hello world avec Bbop, affichage d'un rectangle blanc. \n

Initialisation de la librairie avec une fenêtre glfw. \n 
```
GLFWwindow *window;
bbopInit(1920,1080,"name",window);
```

Mise en place d'une Scene pour afficher notre premier rectangle. \n
```
Scene scene;
```

Creation d'un rectangle. \n
```
RectangleShape rectangle;
rectangle.setPosition(100.f,100.f); //changement de position 
rectangle.setSize(500.f,500.f); //changement de la taille du rectangle
```

Exemple dans une boucle d'affichage avec une fenêtre glfw. \n
```
int main() {
  
  GLFWwindow * window;
  bbopInit(1920,1080,"name",window);
  
  Scene scene;

  RectangleShape rectangle;
  rectangle.setPosition(100.f, 100.f);
  rectangle.setSize(500.f,500.f);

  while (!glfwWindowShouldClose(window))
  {
    // Nettoyage de la fenêtre
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);

    // On 'active' la scene pour donner au shader opengl les variables uniforms
    scene.Use();

    // Affichage du rectangle
    scene.Draw(rectangle);

    // Faire le rendue du frame buffer de la fenêtre
    scene.render();
    
    // Verfication d'erreur opengl
    bbopErrorCheck();

    // Passage du front buffer pour afficher le rendue opengl sur la fenêtre glfw 
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  // Suppression de la fenêtre
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}
```

## Forme géométrique / Shape

Toutes les formes géométriques hérites de la class mère Shape, elle ont donc en commun la plus part de leurs attribut mais les utilisent de différente manières. \n
Ces attributs sont tous accessible avec des getters et setters. \n

Attributs communs. \n
```
Vector2f position; //position
Vector2f size; //taille
Vector2f origin; //origine
float rotation; //angle de rotation en radians
float alpha; //transparence
Vector3i Color; // Couleur au format rgb
CollisionBox shapeCollisionBox: // boîte de collision
bool autoUpdateCollision; // Si true, la boîte de collision se met à jour automatiquement (true par défault)
```

Toute les Shape hérite de BbopDrawable, qui est la class mère de tous les objets dessinables de la librairie. \n

### Rectangle / RectangleShape

Le rectangle est la plus simple de la librairie,

### Forme Convec / ConvexShape

todo

#### Cercle / CircleShape

todo

#### Et les triangles ?

todo \n

### Sprite

todo

#### Sprite animé

todo

## Scene 

todo

## Camera

todo

## Collision

todo

## Light

todo

## Map

todo

## Math 

todo 

## Texture

todo
