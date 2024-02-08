#include "../include/sceneClass.h"

Scene::Scene()
  : sceneShader("shaders/defaultVertex.vert", "shaders/defaultFragment.frag")
{
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  ambiantLightValue = 0.5f;
}

void Scene::Draw()
{
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc, 1.0f*ambiantLightValue,1.0f*ambiantLightValue,1.0f*ambiantLightValue,1.0f);
  for(auto& object : objectsVector){
    object->Draw();
  }
}

void Scene::addSpriteObject(Sprite* object)
{
  objectsVector.push_back(object);
}
