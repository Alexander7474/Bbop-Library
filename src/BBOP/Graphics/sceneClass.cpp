#include "../../../include/BBOP/Graphics/sceneClass.h"

Scene::Scene()
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(1.0f),
    ambiantLightColor(Vector3i(255,255,255)),
    ambiantLightLoc(sceneShader.getUniformLoc("ambiantLight")),
    renderModeLoc(sceneShader.getUniformLoc("renderMode")),
    ambiantLight(Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f)))
{}

Scene::Scene(float nAmbiantLightValue, Vector3i nAmbiantLightColor)
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(nAmbiantLightValue),
    ambiantLightColor(nAmbiantLightColor)
{
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
}

Scene::~Scene() {}

void Scene::Use()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  sceneShader.Activate();
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_SIZE.x), static_cast<float>(BBOP_WINDOW_SIZE.y), 0.0f, -1.0f, 1.0f);
  glUniformMatrix4fv(sceneShader.getUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniform4f(ambiantLightLoc,ambiantLight.x,ambiantLight.y,ambiantLight.z,1.0f);
}

void Scene::Draw(BbopDrawable& spr)
{
  
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
