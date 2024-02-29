#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "textureClass.h"
#include "collisonBoxClass.h"
#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "shapeClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Sprite : public Shape
{
public:
  Sprite(Texture nTexture);
  Sprite();
  ~Sprite();

  void Draw(GLint renderModeLoc) const override;
  void Delete();
  void setTexture(Texture nTexture);
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void updateVBOAlpha() override;
  void move(Vector2f vecM);
  bool getRGBFilterState();
  void setRGBFilterState(bool etat);
private:
  Texture* spriteTexture;
protected:
  GLfloat vertices[32];
  GLuint indices[6];
  bool isRGBFilter;
 };

class NoTextureSprite : public Sprite
{
public:
  void Draw(GLint renderModeLoc) const override;
};

#endif // !SPRITE_CLASS_H
