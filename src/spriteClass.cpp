#include "../include/spriteClass.h"

Sprite::Sprite(const char* textureFileName, GLFWwindow* win)
  : spriteShader("shaders/defaultTexture.vert", "shaders/defaultTexture.frag"),
    spriteTexture(textureFileName),
    spriteVBO(spriteVertices, sizeof(spriteVertices), GL_DYNAMIC_DRAW),
    spriteEBO(spriteIndices, sizeof(spriteIndices))
{
  //initialisation des vertices et des indices a 0.0f avant de build le vao
  for(int i = 0; i < (int)(sizeof(spriteVertices)/sizeof(GLfloat)); i++)
    spriteVertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(spriteIndices)/sizeof(GLuint)); i++)
    spriteIndices[i] = 0;
  spriteWindow = win;
  // Build du vao
  width = (float)spriteTexture.getWidth(); height = (float)spriteTexture.getHeight();
  x = 0.0f;y = 0.0f;
  originX = 0.0f; originY = 0.0f;
  glfwGetWindowSize(spriteWindow, &windowX, &windowY);
  buildVAO();
  cout << "Sprite created with texture " << textureFileName << endl;
}

void Sprite::buildVAO()
{
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  // init sprite and texture coordinate ########################################
  //top right
  spriteVertices[0] = ((x+originX+width)/(windowX/2.0f))-1.0f; spriteVertices[1] = ((-y-originY)/(windowY/2.0f))+1.0f;
  //botton right
  spriteVertices[8] = ((x+originX+width)/(windowX/2.0f))-1.0f; spriteVertices[9] = ((-y-originY-height)/(windowY/2.0f))+1.0f;
  //bottom left
  spriteVertices[16] = ((x+originX)/(windowX/2.0f))-1.0f; spriteVertices[17] = ((-y-originY-height)/(windowY/2.0f))+1.0f;
  //top left
  spriteVertices[24] = ((x+originX)/(windowX/2.0f))-1.0f; spriteVertices[25] = ((-y-originY)/(windowY/2.0f))+1.0f;
  //texture coo
  spriteVertices[6] = 1.0f;spriteVertices[7] = 1.0f;spriteVertices[14] = 1.0f;spriteVertices[31] = 1.0f;
  spriteIndices[0] = 0;spriteIndices[1] = 1;spriteIndices[2] = 3;spriteIndices[3] = 1;spriteIndices[4] = 2;spriteIndices[5] = 3;
  spriteVAO.Bind();
  spriteVBO.update(spriteVertices, sizeof(spriteVertices));
  spriteEBO.update(spriteIndices, sizeof(spriteIndices));
  spriteVAO.LinkVBO(spriteVBO, 0, 3, 8, 0);
  spriteVAO.LinkVBO(spriteVBO, 1, 3, 8, 3);
  spriteVAO.LinkVBO(spriteVBO, 2, 2, 8, 6);
  spriteVAO.Unbind();
  spriteVBO.Unbind();
  spriteEBO.Unbind();
}

void Sprite::updateVBO()
{
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  // init sprite and texture coordinate ########################################
  //top right
  spriteVertices[0] = ((x+originX+width)/(windowX/2.0f))-1.0f; spriteVertices[1] = ((-y-originY)/(windowY/2.0f))+1.0f;
  //botton right
  spriteVertices[8] = ((x+originX+width)/(windowX/2.0f))-1.0f; spriteVertices[9] = ((-y-originY-height)/(windowY/2.0f))+1.0f;
  //bottom left
  spriteVertices[16] = ((x+originX)/(windowX/2.0f))-1.0f; spriteVertices[17] = ((-y-originY-height)/(windowY/2.0f))+1.0f;
  //top left
  spriteVertices[24] = ((x+originX)/(windowX/2.0f))-1.0f; spriteVertices[25] = ((-y-originY)/(windowY/2.0f))+1.0f;
  spriteVBO.update(spriteVertices, sizeof(spriteVertices));
}

void Sprite::Draw() 
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  spriteShader.Activate();
  spriteTexture.Bind();
  spriteVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::setPosition(float nx, float ny)
{
  x = nx;y = ny; 
  updateVBO();
}

float Sprite::getPositionX()
{
  return x;
}

float Sprite::getPositionY()
{
  return y;
}

void Sprite::setSize(float nWidth, float nHeight)
{
  width = nWidth;height = nHeight;
  updateVBO();
}

float Sprite::getWidth()
{
  return width;
}

float Sprite::getHeight()
{
  return height;
}

void Sprite::setOrigin(float nOriginX, float nOriginY)
{
  originX = nOriginX;originY = nOriginY; 
  updateVBO();
}

float Sprite::getOriginX()
{
  return originX;
}

float Sprite::getOriginY()
{
  return originY;
}
