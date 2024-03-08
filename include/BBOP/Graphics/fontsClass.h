#ifndef FONTS_CLASS_H
#define FONTS_CLASS_H

#include "bbopGlobal.h"
#include "bbopMathClass.h"
#include "spriteClass.h"
#include <iostream>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    Vector2f size;       // Size of glyph
    Vector2f bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

void loadFontTexture(const char* fontPath, int fontSize, Character* charList, int numTextures);

class TexteBox : public BbopDrawable
{
public:
  TexteBox(const char * nTexte, int glyphSize, const char* ttfPath);
  TexteBox(const TexteBox& other);
  ~TexteBox();

  TexteBox& operator=(const TexteBox& other);

  Vector2f getPosition();
  void setPosition(Vector2f nPos);
  Vector2f getOrigin();
  void setOrigin(Vector2f nOrigin);
  Vector3i getColor();
  void setColor(Vector3i nRGB);
  float getAlpha();
  void setAlpha(float nAlpha);
  float getRotation();
  void setRotation(float nRotation);
  const char* getTexte();
  void setTexte(const char* nTexte);
  void buildTexteBox();
  void Draw(GLint renderModeLoc) const override;
private:
  Character charL[128]; 
  Vector2f pos;
  Vector2f origin;
  float rotation;
  Vector3i RGB;
  float alpha;
  const char* texte;
  unsigned int sizeTexte;
  NoTextureSprite* glyphList;
  float offset;
};

#endif // !FONTS_CLASS_H
