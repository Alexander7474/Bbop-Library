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
    sceneLightShader(lightVertex, lightFragment),
    ambiantLightValue(nAmbiantLightValue),
    ambiantLightColor(nAmbiantLightColor),
    sceneCamera(nullptr)
{
  //mise en place adresse mem du shader 
  ambiantLight = Vector3f(ambiantLightValue*(ambiantLightColor.x/255.0f), ambiantLightValue*(ambiantLightColor.y/255.0f), ambiantLightValue*(ambiantLightColor.z/255.0f));
  ambiantLightLoc = sceneShader.getUniformLoc("ambiantLight");
  renderModeLoc = sceneShader.getUniformLoc("renderMode");
  projectionLoc = sceneShader.getUniformLoc("projection");

  //mise en place adresse mem du light shader
  nLightLoc = sceneLightShader.getUniformLoc("nLight");
  lightCamScaleLoc = sceneLightShader.getUniformLoc("camScale");
  lightProjectionLoc = sceneLightShader.getUniformLoc("projection");
  lightProjectionCamLoc = sceneLightShader.getUniformLoc("projectionCam");
  lightWindowSizeLoc = sceneLightShader.getUniformLoc("windowSize");
  lightWindowResoLoc = sceneLightShader.getUniformLoc("windowResolution");
  glGenBuffers(1, &lightsUBO);
  glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
  glBufferData(GL_UNIFORM_BUFFER, 100 * sizeof(UniformLight), &lightsVec[0], GL_DYNAMIC_DRAW);
  
  //gestion du frameBuffer 
  glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

  //textureBuffer utilisé pour afficher le frameBuffer 
  glGenTextures(1, &textureColorBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);

  frameBufferSprite.setPosition(0,0);

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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // activation du frame buffer 
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

  //activation du shader et transfert des données nécessaire 
  sceneShader.Activate();
  glUniform4f(ambiantLightLoc,ambiantLight.x,ambiantLight.y,ambiantLight.z,1.0f);

  //definition de la projection de la scene 
  glm::mat4 projection;
  if (sceneCamera != nullptr){
    projection = glm::ortho(sceneCamera->camX.x, sceneCamera->camX.y, sceneCamera->camY.y, sceneCamera->camY.x, -1.0f, 1.0f);
  }else{
    projection = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_RESOLUTION.x), static_cast<float>(BBOP_WINDOW_RESOLUTION.y), 0.0f, -1.0f, 1.0f);
  }
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

 }

void Scene::useCamera(Camera* camAddr)
{
  sceneCamera = camAddr;
}

void Scene::Draw(const BbopDrawable& spr) const
{
  spr.Draw(renderModeLoc);
}

void Scene::DrawFrameBuffer(const NoTextureSprite& spr) const
{
  spr.DrawAsFrameBuffer();
}

void Scene::render()
{
  //unbind du framebuffer pour le rendre sur l'écran
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  sceneLightShader.Activate();
  glUniform2f(lightWindowResoLoc, BBOP_WINDOW_RESOLUTION.x, BBOP_WINDOW_RESOLUTION.y);
  glUniform2f(lightWindowSizeLoc, BBOP_WINDOW_SIZE.x, BBOP_WINDOW_SIZE.y);

  //definition de la projection de la scene (utile pour la lumière)
  glm::mat4 projectionCam;
  if (sceneCamera != nullptr){
    projectionCam = glm::ortho(sceneCamera->camX.x, sceneCamera->camX.y, sceneCamera->camY.y, sceneCamera->camY.x, -1.0f, 1.0f);
    glUniform1f(lightCamScaleLoc, sceneCamera->getScale());
  }else{
    projectionCam = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_RESOLUTION.x), static_cast<float>(BBOP_WINDOW_RESOLUTION.y), 0.0f, -1.0f, 1.0f);
    glUniform1f(lightCamScaleLoc, 1.f);
  }
  glUniformMatrix4fv(lightProjectionCamLoc, 1, GL_FALSE, glm::value_ptr(projectionCam));
  
  //projection pour afficher la texture du framebuffer
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(BBOP_WINDOW_RESOLUTION.x), static_cast<float>(BBOP_WINDOW_RESOLUTION.y), 0.0f, -1.0f, 1.0f);
  glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

  //transfert des lumières
  glUniform1i(nLightLoc, lightsVec.size());
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, lightsUBO);
  glBufferSubData(GL_UNIFORM_BUFFER, 0, lightsVec.size() * sizeof(UniformLight), &lightsVec[0]);
  lightsVec.clear();

  frameBufferSprite.setSize(BBOP_WINDOW_RESOLUTION.x, BBOP_WINDOW_RESOLUTION.y);

  glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
  DrawFrameBuffer(frameBufferSprite);

  //cleaning the frame buffer 
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
