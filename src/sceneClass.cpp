#include "../include/sceneClass.h"

Scene::Scene()
  : sceneShader("shaders/defaultVertex.vert", "shaders/defaultFragment.frag")
{
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  ambiantLightValue = 1.0f;
}

void Scene::Use()
{
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc, 1.0f*ambiantLightValue,1.0f*ambiantLightValue,1.0f*ambiantLightValue,1.0f);
}
