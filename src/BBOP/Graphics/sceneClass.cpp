#include "../../../include/BBOP/Graphics/sceneClass.h"

#include <iostream>

Scene::Scene()
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(1.0f),
    ambiantLightColor(Vector3i(255,255,255)),
    ambiantLightLoc(sceneShader.getUniformLoc("ambiantLight")),
    renderModeLoc(sceneShader.getUniformLoc("renderMode")),
    ambiantLight(Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f))),
    sceneCamera(nullptr)
{}

Scene::Scene(float nAmbiantLightValue, Vector3i nAmbiantLightColor)
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(nAmbiantLightValue),
    ambiantLightColor(nAmbiantLightColor),
    sceneCamera(nullptr)
{
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
  windowSizeLoc = sceneShader.getUniformLoc("windowSize");
  windowResoLoc = sceneShader.getUniformLoc("windowResolution");
  nLightLoc = sceneShader.getUniformLoc("nLight");
  glGenBuffers(1, &lightsUBO);
  glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
  glBufferData(GL_UNIFORM_BUFFER, lightsVec.size() * sizeof(UniformLight), &lightsVec[0], GL_DYNAMIC_DRAW);
}

Scene::~Scene() {}

void Scene::Use(GLFWwindow*& window)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc,ambiantLight.x,ambiantLight.y,ambiantLight.z,1.0f);
  int width, height;
  glfwGetWindowSize(window, &width, &height);
  glUniform2f(windowSizeLoc,width,height);
  glUniform2f(windowResoLoc,static_cast<float>(BBOP_WINDOW_SIZE.x),static_cast<float>(BBOP_WINDOW_SIZE.y));
  glUniform1i(nLightLoc, 3);
  glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, lightsVec.size() * sizeof(UniformLight), &lightsVec[0]);
}

void Scene::useCamera(Camera* camAddr)
{
  sceneCamera = camAddr;
}

void Scene::Draw(BbopDrawable& spr)
{
  glm::mat4 projection;
  if (sceneCamera != nullptr)
    projection = glm::ortho(sceneCamera->camX.x, sceneCamera->camX.y, sceneCamera->camY.y, sceneCamera->camY.x, -1.0f, 1.0f);
  else
    projection = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_SIZE.x), static_cast<float>(BBOP_WINDOW_SIZE.y), 0.0f, -1.0f, 1.0f);
  glUniformMatrix4fv(sceneShader.getUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(projection));
  spr.Draw(renderModeLoc);
}

void Scene::setAmbiantLightColor(Vector3i nAmbiantLightColor)
{
  ambiantLightColor = nAmbiantLightColor;
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
}

Vector3i Scene::getAmbiantLightColor()
{
  return ambiantLightColor;
}

void Scene::setAmbiantLightValue(float nAmbiantLightValue)
{
  ambiantLightValue = nAmbiantLightValue;
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
}

float Scene::getAmbiantLightValue()
{
  return ambiantLightValue;
}

void Scene::addLight(Light& l)
{
  UniformLight nLight;
}
