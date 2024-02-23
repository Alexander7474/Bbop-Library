#include "../../../include/BBOP/Graphics/sceneClass.h"
#include "../../../include/BBOP/Graphics/shaders.h"

Scene::Scene()
  : sceneShader(defaultVertex, defaultFragment)
{
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  ambiantLightValue = 1.0f;
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
}

void Scene::Use()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc, 1.0f*ambiantLightValue,1.0f*ambiantLightValue,1.0f*ambiantLightValue,1.0f);
}

void Scene::Delete()
{
  sceneShader.Delete();
}

void Scene::Draw(BbopDrawable& spr)
{
  spr.Draw(renderModeLoc);
}
