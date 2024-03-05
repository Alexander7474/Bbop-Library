#include "../../../include/BBOP/Graphics/spriteClass.h"

Sprite::Sprite(Texture nTexture)
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices)),
    spriteTexture(new Texture(nTexture)),
    isRGBFilter(false)
{
  size.x = spriteTexture->getWidth(); size.y = spriteTexture->getHeight();
  // Build du vao
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  buildVAO();
}

Sprite::Sprite()
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices)),
    spriteTexture(nullptr),
    isRGBFilter(true)
{
  size.x = 50.0f; size.y = 50.0f;
  buildVAO();
}

Sprite::~Sprite()
{
  delete spriteTexture;
}

void Sprite::buildVAO()
{
  //initialisation des vertices et des indices a 0.0f avant de build le vao
  for(int i = 0; i < (int)(sizeof(vertices)/sizeof(GLfloat)); i++)
    vertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(indices)/sizeof(GLuint)); i++)
    indices[i] = 0;
  // init sprite and texture coordinate ########################################
  // vecteur position normalizé
  Vector2f pTL(-origin.x, -origin.y);
  Vector2f pTR(pTL.x+size.x,pTL.y);
  Vector2f pBR(pTR.x,pTL.y+size.y);
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x+pos.x; vertices[1] = pTR.y+pos.y;
  //botton right
  vertices[8] = pBR.x+pos.x; vertices[9] = pBR.y+pos.y;
  //bottom left
  vertices[16] = pBL.x+pos.x; vertices[17] = pBL.y+pos.y;
  //top left
  vertices[24] = pTL.x+pos.x; vertices[25] = pTL.y+pos.y;
 /// color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 32;i+=8){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;vertices[i+5] = alpha;
  }
  //texture coo
  vertices[6] = 1.0f;vertices[7] = 1.0f;vertices[14] = 1.0f;vertices[31] = 1.0f;
  indices[0] = 0;indices[1] = 1;indices[2] = 3;indices[3] = 1;indices[4] = 2;indices[5] = 3;
  shapeVAO.Bind();
  shapeVBO.update(vertices, sizeof(vertices));
  shapeEBO.update(indices, sizeof(indices));
  shapeVAO.LinkVBO(shapeVBO, 0, 2, 8, 0);
  shapeVAO.LinkVBO(shapeVBO, 1, 4, 8, 2);
  shapeVAO.LinkVBO(shapeVBO, 2, 2, 8, 6);
  shapeVAO.Unbind();
  shapeVBO.Unbind();
  shapeEBO.Unbind();
}

void Sprite::updateVBO()
{
  //  coordinate change ######################################## 
  // vecteur position normalizé
  Vector2f pTL(-origin.x, -origin.y);
  Vector2f pTR(pTL.x+size.x,pTL.y);
  Vector2f pBR(pTR.x,pTL.y+size.y);
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x+pos.x; vertices[1] = pTR.y+pos.y;
  //botton right
  vertices[8] = pBR.x+pos.x; vertices[9] = pBR.y+pos.y;
  //bottom left
  vertices[16] = pBL.x+pos.x; vertices[17] = pBL.y+pos.y;
  //top left
  vertices[24] = pTL.x+pos.x; vertices[25] = pTL.y+pos.y;
  
  shapeVBO.update(vertices, sizeof(vertices));
  if (autoUpdateCollision){
    shapeCollisionBox.setPosition(pos);
    shapeCollisionBox.setSize(size);
    shapeCollisionBox.setOrigin(origin);
  }
}

void Sprite::updateVBORGB()
{
  // color change ########################################
  float r = RGB.x/255.0f;float g = RGB.y/255.0f;float b = RGB.z/255.0f;
  for(int i = 0; i < 32;i+=8){
    vertices[i+2] = r;vertices[i+3] = g; vertices[i+4] = b;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void Sprite::updateVBOAlpha()
{
  // alpha change ########################################
  for(int i = 0; i < 32;i+=8){
    vertices[i+5] = alpha;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void Sprite::Draw(GLint renderModeLoc) const 
{
  if (!isRGBFilter)
    glUniform1i(renderModeLoc, BBOP_SHADER_MODE_TEXTURE);
  else
    glUniform1i(renderModeLoc, BBOP_SHADER_MODE_MIX);
  spriteTexture->Bind();
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  shapeVAO.Unbind();
  spriteTexture->Unbind();
}

void Sprite::Delete()
{
  shapeVAO.Delete();
  shapeVBO.Delete();
  shapeEBO.Delete();
  spriteTexture->Delete();
}

void Sprite::setTexture(Texture nTexture)
{
  delete spriteTexture;
  spriteTexture = new Texture(nTexture);
}

void Sprite::setRGBFilterState(bool etat)
{
  isRGBFilter = etat;
}

bool Sprite::getRGBFilterState()
{
  return isRGBFilter;
}

void NoTextureSprite::Draw(GLint renderModeLoc) const 
{
  if (!isRGBFilter)
    glUniform1i(renderModeLoc, BBOP_SHADER_MODE_TEXTURE);
  else
    glUniform1i(renderModeLoc, BBOP_SHADER_MODE_MIX);
  shapeVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

