#ifndef FONTS_CLASS_H
#define FONTS_CLASS_H

#include "textureClass.h"
#include <iostream>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void loadFontTexture(const char* fontPath, int fontSize, GLuint* textures, int numTextures);

class Texte
{
public:
  Texte();
};

#endif // !FONTS_CLASS_H
