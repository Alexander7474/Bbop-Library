#include "../../../include/BBOP/Graphics/spriteClass.h"

Sprite::Sprite(const char* textureFileName, GLFWwindow* win)
  : spriteTexture(textureFileName),
    spriteVBO(spriteVertices, sizeof(spriteVertices), GL_DYNAMIC_DRAW),
    spriteEBO(spriteIndices, sizeof(spriteIndices)),
    spriteWindow(win),
    pos(0.0f,0.0f),
    size((float)spriteTexture.getWidth(), (float)spriteTexture.getHeight()),
    origin(0.0f, 0.0f),
    RGBFilter(255.0f,255.0f,255.0f),
    spriteCollisionBox(pos, origin, size)
{
  isRGBFilter = false;
    // Build du vao
  glfwGetWindowSize(spriteWindow, &windowX, &windowY);
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  buildVAO();
  autoUpdateCollision = false;
  cout << "Sprite created with texture " << textureFileName << endl;
}

void Sprite::buildVAO()
{
  //initialisation des vertices et des indices a 0.0f avant de build le vao
  for(int i = 0; i < (int)(sizeof(spriteVertices)/sizeof(GLfloat)); i++)
    spriteVertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(spriteIndices)/sizeof(GLuint)); i++)
    spriteIndices[i] = 0;
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
  // sprite coordinate change ########################################
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

void Sprite::updateVBORGB()
{
  // color change ########################################
  //top right
  spriteVertices[3] = RGBFilter.x/255.0f; spriteVertices[4] = RGBFilter.y/255.0f; spriteVertices[5] = RGBFilter.z/255.0f;
  //botton right
  spriteVertices[11] = RGBFilter.x/255.0f; spriteVertices[12] = RGBFilter.y/255.0f; spriteVertices[13] = RGBFilter.z/255.0f;
  //bottom left
  spriteVertices[19] = RGBFilter.x/255.0f; spriteVertices[20] = RGBFilter.y/255.0f; spriteVertices[21] = RGBFilter.z/255.0f;
  //top left
  spriteVertices[27] = RGBFilter.x/255.0f; spriteVertices[28] = RGBFilter.y/255.0f; spriteVertices[29] = RGBFilter.z/255.0f;
  spriteVBO.update(spriteVertices, sizeof(spriteVertices));
}

void Sprite::Draw(GLint renderModeLoc) const 
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!isRGBFilter)
    glUniform1i(renderModeLoc, BIBIBOP_SHADER_MODE_TEXTURE);
  else
    glUniform1i(renderModeLoc, BIBIBOP_SHADER_MODE_MIX);
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

void Sprite::setRGBFilterState(bool etat)
{
  isRGBFilter = etat;
}

void Sprite::setRGBFilter(Vector3i nRGB)
{
  RGBFilter = nRGB;
  updateVBORGB();
}
