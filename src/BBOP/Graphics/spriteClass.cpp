#include "../../../include/BBOP/Graphics/spriteClass.h"

Sprite::Sprite(const char* textureFileName)
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices)),
    spriteTexture(textureFileName),
    spriteCollisionBox(pos, origin, size)
{
  isRGBFilter = false;
    // Build du vao
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  buildVAO();
  autoUpdateCollision = true;
  cout << "Sprite created with texture " << textureFileName << endl;
}

void Sprite::buildVAO()
{
  //initialisation des vertices et des indices a 0.0f avant de build le vao
  for(int i = 0; i < (int)(sizeof(vertices)/sizeof(GLfloat)); i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(indices)/sizeof(GLuint)); i++)
    indices[i] = 0;
  // init sprite and texture coordinate ########################################
  //top right
  vertices[0] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[1] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //botton right
  vertices[8] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[9] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //bottom left
  vertices[16] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[17] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //top left
  vertices[24] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[25] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //texture coo
  vertices[6] = 1.0f;vertices[7] = 1.0f;vertices[14] = 1.0f;vertices[31] = 1.0f;
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind();
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 3, 8, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 3, 8, 3);
  shapeVAO.LinkVBO(shapeVBO, 2, 2, 8, 6);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
}

void Sprite::updateVBO()
{
  // sprite coordinate change ########################################
  //top right
  vertices[0] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[1] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //botton right
  vertices[8] = ((pos.x-origin.x+size.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[9] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //bottom left
  vertices[16] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[17] = ((-pos.y+origin.y-size.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //top left
  vertices[24] = ((pos.x-origin.x)/(BIBIBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[25] = ((-pos.y+origin.y)/(BIBIBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  shapeVBO.update(vertices, sizeof(vertices));
  if (autoUpdateCollision){
    spriteCollisionBox.setPosition(pos);
    spriteCollisionBox.setSize(size);
    spriteCollisionBox.setOrigin(origin);
  }
}

void Sprite::updateVBORGB()
{
  // color change ########################################
  //top right
  vertices[3] = RGB.x/255.0f; vertices[4] = RGB.y/255.0f; vertices[5] = RGB.z/255.0f;
  //botton right
  vertices[11] = RGB.x/255.0f; vertices[12] = RGB.y/255.0f; vertices[13] = RGB.z/255.0f;
  //bottom left
  vertices[19] = RGB.x/255.0f; vertices[20] = RGB.y/255.0f; vertices[21] = RGB.z/255.0f;
  //top left
  vertices[27] = RGB.x/255.0f; vertices[28] = RGB.y/255.0f; vertices[29] = RGB.z/255.0f;
  shapeVBO.update(vertices, sizeof(vertices));
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
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Sprite::Delete()
{
  shapeVAO.Delete();
  shapeVBO.Delete();
  shapeEBO.Delete();
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

void Sprite::move(Vector2f vecM)
{
  pos.x += vecM.x; pos.y += vecM.y;
  updateVBO();
}

void Sprite::setAutoUpdateCollision(bool etat)
{
  autoUpdateCollision = etat;
}

void Sprite::setRGBFilterState(bool etat)
{
  isRGBFilter = etat;
}

