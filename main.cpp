////////////////////////////////////////////////////////////////////
//CECI N'EST QU'UN EXEMPLE POUR TESTER SI BBOP EST BIEN INSTALLER
////////////////////////////////////////////////////////////////////
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "include/BBOP/Graphics.h"
#include "include/BBOP/Graphics/bbopFunc.h"
#include "include/BBOP/Graphics/bbopGlobal.h"

using namespace std;

struct Light { 
  glm::vec2 pos; // Position de la source de lumière (2D)
  float p0[2];
  glm::vec3 color; // Couleur de la lumière
  float intensity; // Intensité de la lumière
  float constantAttenuation; // Attnuation constante
  float linearAttenuation; // Attnuation linéaire
  float quadraticAttenuation; // Attnuation quadratique
  float p1[1];
};

int main() {
  
  GLFWwindow * window;
  bbopInit(956,1044,"test",window);
  
  //Creation de la scene pour afficher nos formes
  cout << "creation de la scene" << endl;
  Scene defaultScene(0.0f,Vector3i(255,255,255));
  //creation d'un rectangle a afficher, par default blanc en haut a gauche de l'image
  cout << "creation du rectangle" << endl;
  RectangleShape defaultRect(Vector2f(100.0f,100.0f),Vector2f(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f),Vector3i(15,182,245),Vector2f(-20.0f,-20.0f));
  RectangleShape bg(Vector2f(956.0f,1044.0f),Vector2f(0.0f,0.0f),Vector3i(100,100,100),Vector2f(0.0f,0.0f));

  cout << "creation du sprite" << endl;
  Sprite defaultSprite(Texture("imgTesting/mario.png"), Vector2f(150.0f,150.0f));
  defaultSprite.setSize(Vector2f(100.0f,100.0f));
  defaultSprite.setOrigin(Vector2f(50.0f,50.0f));

  cout << "creation de la forme convex" << endl;
  Vector2f list[6] = {Vector2f(100.0f,100.0f),Vector2f(170.0f,10.0f),Vector2f(189.0f,75.0f),Vector2f(189.0f,199.0f),Vector2f(32.0f,112.0f),Vector2f(0.0f,0.0f)};
  ConvexShape defaultConvex(6,list,Vector2f(1.0f,1.0f),Vector2f(650.0f,250.0f));
  defaultConvex.setColor(Vector3i(100,0,255));

  CircleShape circleDefault(99, 50.0f);

  Camera cam(defaultSprite.getPosition(),1.0f);

  ///////////////
  vector<Light> lightsList;
  Light testLight;
  testLight.pos = glm::vec2(100.0,100.0);
  testLight.color = glm::vec3(1.0,1.0,1.0);
  testLight.intensity = 0.2f;
  testLight.constantAttenuation = 0.2f;
  testLight.linearAttenuation = 0.5f;
  testLight.quadraticAttenuation = 0.01f;
  Light utestLight;
  utestLight.pos = glm::vec2(900.0,900.0);
  utestLight.color = glm::vec3(1.0,0.0,1.0);
  utestLight.intensity = 0.5f;
  utestLight.constantAttenuation = 0.1f;
  utestLight.linearAttenuation = 0.1f;
  utestLight.quadraticAttenuation = 1.1f;
  Light ytestLight;
  ytestLight.pos = glm::vec2(900.0,100.0);
  ytestLight.color = glm::vec3(0.0,1.0,1.0);
  ytestLight.intensity = 0.2f;
  ytestLight.constantAttenuation = 0.2f;
  ytestLight.linearAttenuation = 0.5f;
  ytestLight.quadraticAttenuation = 0.01f;
  lightsList.push_back(utestLight);
  lightsList.push_back(testLight);
  lightsList.push_back(ytestLight);
  GLuint lightsUBO;
  glGenBuffers(1, &lightsUBO);
  glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
  glBufferData(GL_UNIFORM_BUFFER, lightsList.size() * sizeof(Light), &lightsList[0], GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, lightsList.size() * sizeof(Light), &lightsList[0]);

  
  //////////////


  // Main while loop
	while (!glfwWindowShouldClose(window))
	{
    bbopCleanWindow(window, Vector3i(0,0,0),1.0);
    glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
    glBufferData(GL_UNIFORM_BUFFER, lightsList.size() * sizeof(Light), &lightsList[0], GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, lightsList.size() * sizeof(Light), &lightsList[0]);

    //////////////////////////////////////////////////////////////
    ///code zone
    //////////////////////////////////////////////////////////////
    
    cam.setPosition(defaultSprite.getPosition());
    defaultScene.Use(window);
    //defaultScene.useCamera(&cam);
    defaultScene.Draw(bg);
    //affichage du rectangle  avec sa rotation
    defaultRect.setRotation(defaultRect.getRotation()+0.01);
    defaultScene.Draw(defaultRect);
    //affichage du sprite mario, texture par default si non trouvé
    defaultScene.Draw(defaultSprite);
    //affichage de la forme convex
    defaultConvex.setRotation(defaultConvex.getRotation()+0.01);
    defaultScene.Draw(defaultConvex);

    defaultScene.Draw(circleDefault);


    bbopDebugCollisionBox(defaultSprite.getCollisionBox(), defaultScene);
    //gestiond des mouvement de mario
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,-5.0f));
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      defaultSprite.move(Vector2f(0.0f,5.0f));
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      defaultSprite.move(Vector2f(5.0f,0.0f));   
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      defaultSprite.move(Vector2f(-5.0f,0.0f));

    if(defaultSprite.getCollisionBox()->checkWithRotation(defaultRect.getCollisionBox()))
      cout << glfwGetTime() << endl;


    //////////////////////////////////////////////////////////////
    
    bbopErrorCheck();

    // Swap the back buffer with the front buffer
	  glfwSwapBuffers(window);
	  glfwPollEvents();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
