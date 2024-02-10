#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "textureClass.h"
#include "collisonBoxClass.h"
#include "bbopMathClass.h"
#include "bbopGlobal.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace std;

class Sprite : public BbopDrawable
{
public:
  Sprite(const char* textureFileName, GLFWwindow* win);

  void Draw(GLint renderModeLoc) const override;
  void Delete();
  void setPosition(Vector2f nPos);
  Vector2f getPosition();
  void setSize(Vector2f nSize);
  Vector2f getSize();
  void setOrigin(Vector2f nOrigin);
  Vector2f getOrigin();
  void setTexture(Texture nTexture);
  void buildVAO();
  void updateVBO();
  void move(Vector2f vecM);
  bool isInCollision(CollisionBox* box);
  CollisionBox* getCollisionBox();
  void setAutoUpdateCollision(bool etat);
private:
  int windowX, windowY;
  Texture spriteTexture;
  VAO spriteVAO;
  VBO spriteVBO;
  EBO spriteEBO;
  GLfloat spriteVertices[32];
  GLuint spriteIndices[6];
  GLFWwindow* spriteWindow;
  Vector2f pos;
  Vector2f size;
  Vector2f origin;
  CollisionBox spriteCollisionBox;
  bool autoUpdateCollision;
 };

#endif // !SPRITE_CLASS_H
