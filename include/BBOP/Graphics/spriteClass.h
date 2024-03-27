#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "textureClass.h"
#include "collisionBoxClass.h"
#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "shapeClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Sprite : public Shape
{
public:
  Sprite(Texture nTexture, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin, float nRotation, float nAlpha);
  Sprite(Texture nTexture, Vector2f nPos, Vector3i nRGB, Vector2f nOrigin);
  Sprite(Texture nTexture, Vector2f nPos);
  Sprite(Texture nTexture);
  Sprite();
  Sprite(const Sprite& other);
  ~Sprite();

  Sprite& operator=(const Sprite& other);

  void Draw(GLint renderModeLoc) const override;
  void Delete();
  void setTexture(Texture nTexture);
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void updateVBOAlpha() override;
  bool getRGBFilterState();
  void setRGBFilterState(bool etat);
  void flipHorizontally();
  void flipVertically();
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
