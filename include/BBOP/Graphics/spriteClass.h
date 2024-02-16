#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "textureClass.h"
#include "collisonBoxClass.h"
#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "shapeClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

class Sprite : public Shape
{
public:
  Sprite(const char* textureFileName);

  void Draw(GLint renderModeLoc) const override;
  void Delete();
  void setTexture(Texture nTexture);
  void buildVAO() override;
  void updateVBO() override;
  void updateVBORGB() override;
  void move(Vector2f vecM);
  void setRGBFilterState(bool etat);
private:
  Texture spriteTexture;
  GLfloat vertices[32];
  GLuint indices[6];
  bool isRGBFilter;
 };

#endif // !SPRITE_CLASS_H
