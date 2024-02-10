#include "../include/spriteClass.h"

Sprite::Sprite(const char* textureFileName, GLFWwindow* win)
  : spriteTexture(textureFileName),
    spriteVBO(spriteVertices, sizeof(spriteVertices), GL_DYNAMIC_DRAW),
    spriteEBO(spriteIndices, sizeof(spriteIndices)),
    spriteWindow(win),
    pos(0.0f,0.0f),
    size((float)spriteTexture.getWidth(), (float)spriteTexture.getHeight()),
    origin(0.0f, 0.0f),
    spriteCollisionBox(pos, origin, size)
{
  //initialisation des vertices et des indices a 0.0f avant de build le vao
  for(int i = 0; i < (int)(sizeof(spriteVertices)/sizeof(GLfloat)); i++)
    spriteVertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(spriteIndices)/sizeof(GLuint)); i++)
    spriteIndices[i] = 0;
  // Build du vao
  glfwGetWindowSize(spriteWindow, &windowX, &windowY);
  buildVAO();
  autoUpdateCollision = false;
  cout << "Sprite created with texture " << textureFileName << endl;
}

void Sprite::buildVAO()
{
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  // init sprite and texture coordinate ########################################
  //top right
  spriteVertices[0] = ((pos.x-origin.x+size.x)/(windowX/2.0f))-1.0f; spriteVertices[1] = ((-pos.y+origin.y)/(windowY/2.0f))+1.0f;
  //botton right
  spriteVertices[8] = ((pos.x-origin.x+size.x)/(windowX/2.0f))-1.0f; spriteVertices[9] = ((-pos.y+origin.y-size.y)/(windowY/2.0f))+1.0f;
  //bottom left
  spriteVertices[16] = ((pos.x-origin.x)/(windowX/2.0f))-1.0f; spriteVertices[17] = ((-pos.y+origin.y-size.y)/(windowY/2.0f))+1.0f;
  //top left
  spriteVertices[24] = ((pos.x-origin.x)/(windowX/2.0f))-1.0f; spriteVertices[25] = ((-pos.y+origin.y)/(windowY/2.0f))+1.0f;
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
  // init sprite and texture coordinate ########################################
  //top right
  spriteVertices[0] = ((pos.x-origin.x+size.x)/(windowX/2.0f))-1.0f; spriteVertices[1] = ((-pos.y+origin.y)/(windowY/2.0f))+1.0f;
  //botton right
  spriteVertices[8] = ((pos.x-origin.x+size.x)/(windowX/2.0f))-1.0f; spriteVertices[9] = ((-pos.y+origin.y-size.y)/(windowY/2.0f))+1.0f;
  //bottom left
  spriteVertices[16] = ((pos.x-origin.x)/(windowX/2.0f))-1.0f; spriteVertices[17] = ((-pos.y+origin.y-size.y)/(windowY/2.0f))+1.0f;
  //top left
  spriteVertices[24] = ((pos.x-origin.x)/(windowX/2.0f))-1.0f; spriteVertices[25] = ((-pos.y+origin.y)/(windowY/2.0f))+1.0f;
  spriteVBO.update(spriteVertices, sizeof(spriteVertices));
}

void Sprite::Draw(GLint renderModeLoc) const 
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glUniform1i(renderModeLoc, BIBIBOP_SHADER_MODE_TEXTURE);
  spriteTexture.Bind();
  spriteVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::Delete()
{
  spriteVAO.Delete();
  spriteVBO.Delete();
  spriteEBO.Delete();
  spriteTexture.Delete();
}

CollisionBox* Sprite::getCollisionBox()
{
  return &spriteCollisionBox;
}

bool Sprite::isInCollision(CollisionBox* box)
{
  return spriteCollisionBox.check(box);
}

void Sprite::setTexture(Texture nTexture)
{
  spriteTexture = nTexture;
}

void Sprite::setPosition(Vector2f nPos)
{
  pos.x = nPos.x;pos.y = nPos.y;
  if (autoUpdateCollision)
    spriteCollisionBox.setPosition(Vector2f(pos.x, pos.y));
  updateVBO();
}

Vector2f Sprite::getPosition()
{
  return pos;
}

void Sprite::setSize(Vector2f nSize)
{
  size.x = nSize.x; size.y = nSize.y;
  if(autoUpdateCollision)
    spriteCollisionBox.setSize(Vector2f(size.x, size.y));
  updateVBO();
}

Vector2f Sprite::getSize()
{
  return size;
}

void Sprite::setOrigin(Vector2f nOrigin)
{
  origin.x = nOrigin.x; origin.y = nOrigin.y; 
  if (autoUpdateCollision)
    spriteCollisionBox.setOrigin(Vector2f(origin.x, origin.y));
  updateVBO();
}

void Sprite::move(Vector2f vecM)
{
  pos.x += vecM.x; pos.y += vecM.y;
  if (autoUpdateCollision)
    spriteCollisionBox.move(vecM);
  updateVBO();
}

Vector2f Sprite::getOrigin()
{
  return origin;
}

void Sprite::setAutoUpdateCollision(bool etat)
{
  autoUpdateCollision = etat;
}
