#include "../../../include/BBOP/Graphics/sceneClass.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(1.0f),
    ambiantLightColor(Vector3i(255,255,255))
{
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
}

Scene::Scene(float nAmbiantLightValue, Vector3i nAmbiantLightColor)
  : sceneShader(defaultVertex, defaultFragment),
    ambiantLightValue(nAmbiantLightValue),
    ambiantLightColor(nAmbiantLightColor)
{
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
}

void Scene::Use()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc,ambiantLight.x,ambiantLight.y,ambiantLight.z,1.0f);
}

void Scene::Draw(BbopDrawable& spr)
{
  glm::mat4 projection = glm::ortho(0.0f, 956.0f, 1044.0f, 0.0f, -1.0f, 1.0f);
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
