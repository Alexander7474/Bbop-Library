#include "../../../include/BBOP/Graphics/spriteClass.h"

Sprite::Sprite(const char* textureFileName)
  : Shape(vertices, sizeof(vertices), indices, sizeof(indices)),
    spriteTexture(textureFileName),
    isRGBFilter(false)
{
    // Build du vao
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  buildVAO();
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
  vertices[0] = ((pos.x-origin.x+size.x)/(BBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[1] = ((-pos.y+origin.y)/(BBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //botton right
  vertices[8] = ((pos.x-origin.x+size.x)/(BBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[9] = ((-pos.y+origin.y-size.y)/(BBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //bottom left
  vertices[16] = ((pos.x-origin.x)/(BBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[17] = ((-pos.y+origin.y-size.y)/(BBOP_WINDOW_SIZE.y/2.0f))+1.0f;
  //top left
  vertices[24] = ((pos.x-origin.x)/(BBOP_WINDOW_SIZE.x/2.0f))-1.0f; vertices[25] = ((-pos.y+origin.y)/(BBOP_WINDOW_SIZE.y/2.0f))+1.0f;
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
  //  coordinate change ########################################
  //  vecteur taille de la fenetre
  Vector2f w(BBOP_WINDOW_SIZE.x/2.0f,BBOP_WINDOW_SIZE.y/2.0f);
  // vecteur position normalizé
  Vector2f pTL(((pos.x-origin.x)/w.x)-1.0f, ((pos.y-origin.y)/w.y)-1.0f);
  Vector2f pTR(pTL.x+(size.x/w.x),pTL.y);
  Vector2f pBR(pTR.x,pTL.y+(size.y/w.y));
  Vector2f pBL(pTL.x,pBR.y);
  //application de la rotation
  float cosAngle = cos(rotation);
  float sinAngle = sin(rotation);
  pTL = Vector2f(pTL.x * cosAngle - pTL.y*sinAngle,pTL.x*sinAngle+pTL.y*cosAngle);
  pTR = Vector2f(pTR.x * cosAngle - pTR.y*sinAngle,pTR.x*sinAngle+pTR.y*cosAngle);
  pBR = Vector2f(pBR.x * cosAngle - pBR.y*sinAngle,pBR.x*sinAngle+pBR.y*cosAngle);
  pBL = Vector2f(pBL.x * cosAngle - pBL.y*sinAngle,pBL.x*sinAngle+pBL.y*cosAngle);
  //top right
  vertices[0] = pTR.x; vertices[1] = -pTR.y;
  //botton right
  vertices[8] = pBR.x; vertices[9] = -pBR.y;
  //bottom left
  vertices[16] = pBL.x; vertices[17] = -pBL.y;
  //top left
  vertices[24] = pTL.x; vertices[25] = -pTL.y;
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
  for(int i = 0; i < 24;i+=8){
    vertices[i+3] = r;vertices[i+4] = g; vertices[i+5] = b;
  }
  shapeVBO.update(vertices, sizeof(vertices));
}

void Sprite::Draw(GLint renderModeLoc) const 
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  if (!isRGBFilter)
    glUniform1i(renderModeLoc, BBOP_SHADER_MODE_TEXTURE);
  else
    glUniform1i(renderModeLoc, BBOP_SHADER_MODE_MIX);
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

void Sprite::setTexture(Texture nTexture)
{
  spriteTexture = nTexture;
}

void Sprite::move(Vector2f vecM)
{
  pos.x += vecM.x; pos.y += vecM.y;
  updateVBO();
}

void Sprite::setRGBFilterState(bool etat)
{
  isRGBFilter = etat;
}

