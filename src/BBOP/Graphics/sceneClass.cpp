/*
 * sceneClass.cpp
 *
 * Ce programme est distribué sous les termes de la Licence Publique
 * Générale GNU, version 3.0, telle que publiée par la Free Software
 * Foundation. Consultez la Licence Publique Générale GNU pour plus de
 * détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU
 * en même temps que ce programme. Si ce n'est pas le cas, consultez
 * <https://www.gnu.org/licenses/>.
 */

#include "../../../include/BBOP/Graphics/sceneClass.h"

#include <cmath>
#include <iostream>

Scene::Scene() : Scene(1.f, Vector3i(255,255,255)) {}

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
  
  //gestion du frameBuffer 
  glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

  //textureBuffer utilisé pour afficher le frameBuffer 
  glGenTextures(1, &textureColorBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    LOGS.push_back("BBOP ERROR -> Frame buffer de la scene incomplé");
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Scene::~Scene() 
{
  
}

void Scene::Use()
{
  // activation du frame buffer 
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);


  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //activation du shader et transfert des données nécessaire 
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

void Scene::Draw(const BbopDrawable& spr) const
{
  glm::mat4 projection;
  float camScale;
  if (sceneCamera != nullptr){
    projection = glm::ortho(sceneCamera->camX.x, sceneCamera->camX.y, sceneCamera->camY.y, sceneCamera->camY.x, -1.0f, 1.0f);
    camScale = sceneCamera->getScale();
  }else{
    projection = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_RESOLUTION.x), static_cast<float>(BBOP_WINDOW_RESOLUTION.y), 0.0f, -1.0f, 1.0f);
    camScale = 1.f;
  }
  glUniformMatrix4fv(sceneShader.getUniformLoc("projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniform1f(sceneShader.getUniformLoc("camScale"), camScale);
  spr.Draw(renderModeLoc);
}

void Scene::render()
{
  //unbind du framebuffer pour le rendre sur l'écran
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  NoTextureSprite spr; 
  spr.setPosition(0,0);
  spr.setSize(BBOP_WINDOW_RESOLUTION.x, BBOP_WINDOW_RESOLUTION.y);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  useCamera(nullptr);
  Draw(spr);
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
  nLight.rotationAngle = -l.getRotationAngle();
  nLight.openAngle = l.getOpenAngle();
  lightsVec.push_back(nLight);
}
