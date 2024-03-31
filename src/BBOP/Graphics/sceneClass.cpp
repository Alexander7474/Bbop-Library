#include "../../../include/BBOP/Graphics/sceneClass.h"

#include <iostream>

Scene::Scene()
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(1.0f),
    ambiantLightColor(Vector3i(255,255,255)),
    ambiantLight(Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f))),
    sceneCamera(nullptr)
{
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
  windowSizeLoc = sceneShader.getUniformLoc("windowSize");
  windowResoLoc = sceneShader.getUniformLoc("windowResolution");
  nLightLoc = sceneShader.getUniformLoc("nLight");
  glGenBuffers(1, &lightsUBO);
  glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
  glBufferData(GL_UNIFORM_BUFFER, 100 * sizeof(UniformLight), &lightsVec[0], GL_DYNAMIC_DRAW);
}

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
  glBufferData(GL_UNIFORM_BUFFER, 100 * sizeof(UniformLight), &lightsVec[0], GL_DYNAMIC_DRAW);
}

Scene::~Scene() {}

void Scene::Use(GLFWwindow*& window)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc,ambiantLight.x,ambiantLight.y,ambiantLight.z,1.0f);
  glUniform2f(windowSizeLoc,BBOP_WINDOW_SIZE.x,BBOP_WINDOW_SIZE.y);
  glUniform2f(windowResoLoc,BBOP_WINDOW_RESOLUTION.x,BBOP_WINDOW_RESOLUTION.y);
  glUniform1i(nLightLoc, lightsVec.size());
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, lightsVec.size() * sizeof(UniformLight), &lightsVec[0]);
  lightsVec.clear();
}

void Scene::useCamera(Camera* camAddr)
{
  sceneCamera = camAddr;
}

void Scene::Draw(BbopDrawable& spr) const
{
  glm::mat4 projection;
  if (sceneCamera != nullptr)
    projection = glm::ortho(sceneCamera->camX.x, sceneCamera->camX.y, sceneCamera->camY.y, sceneCamera->camY.x, -1.0f, 1.0f);
  else
    projection = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_RESOLUTION.x), static_cast<float>(BBOP_WINDOW_RESOLUTION.y), 0.0f, -1.0f, 1.0f);
  glUniformMatrix4fv(sceneShader.getUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(projection));
  spr.Draw(renderModeLoc);
}

void Scene::setAmbiantLightColor(const Vector3i &nAmbiantLightColor)
{
  ambiantLightColor = nAmbiantLightColor;
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
}

const Vector3i &Scene::getAmbiantLightColor() const
{
  return ambiantLightColor;
}

void Scene::setAmbiantLightValue(float nAmbiantLightValue)
{
  ambiantLightValue = nAmbiantLightValue;
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
}

float Scene::getAmbiantLightValue() const
{
  return ambiantLightValue;
}

void Scene::addLight(Light& l)
{
  UniformLight nLight;
  nLight.pos.x = l.getPosistion().x; nLight.pos.y = l.getPosistion().y;
  nLight.color.x = l.getColor().x/255.0f; nLight.color.y = l.getColor().y/255.0f; nLight.color.z = l.getColor().z/255.0f;
  nLight.intensity = l.getIntensity();
  nLight.linearAttenuation = l.getLinear();
  nLight.constantAttenuation = l.getConstant();
  nLight.quadraticAttenuation = l.getQuadratic();
  lightsVec.push_back(nLight);
}
