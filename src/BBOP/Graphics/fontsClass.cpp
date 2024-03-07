#include "../../../include/BBOP/Graphics/fontsClass.h"
#include <algorithm>
#include <cstring>
#include <vector>

// Charge une police TrueType en tant que texture OpenGL
void loadFontTexture(const char* fontPath, int fontSize, Character* charList, int numTextures) {
   
  FT_Library ft;
    if (FT_Init_FreeType(&ft) != 0) {
        std::cerr << "Erreur lors de l'initialisation de FreeType" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face) != 0) {
        std::cerr << "Erreur lors du chargement de la police de caractères" << std::endl;
        FT_Done_FreeType(ft);
        return;
    }

    if (FT_Set_Pixel_Sizes(face, 0, fontSize) != 0) {
        std::cerr << "Erreur lors du redimensionnement de la police de caractères" << std::endl;
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return;
    }


    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Désactive le padding pour la texture
    
    // Générer les textures OpenGL pour chaque glyphe
    for (int i = 0; i < numTextures; ++i) {
        char character = static_cast<char>(i);
        if (FT_Load_Char(face, character, FT_LOAD_RENDER) != 0) {
            std::cerr << "Erreur lors du chargement du glyphe " << character << std::endl;
            continue;
        }

        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

        // Inverser le glyph
        for (unsigned int row = 0; row < face->glyph->bitmap.rows / 2; ++row) {
          for (unsigned int col = 0; col < face->glyph->bitmap.width; ++col) {
            std::swap(face->glyph->bitmap.buffer[row * face->glyph->bitmap.width + col],
                      face->glyph->bitmap.buffer[(face->glyph->bitmap.rows - row - 1) * face->glyph->bitmap.width + col]);
          }
        }
        
        // Générer une texture OpenGL pour le glyphe
    
        glGenTextures(1, &charList[i].TextureID);
        glBindTexture(GL_TEXTURE_2D, charList[i].TextureID);
        

        // Create a new image buffer for RGBA format
        std::vector<unsigned char> rgbaBuffer(face->glyph->bitmap.width * face->glyph->bitmap.rows * 4); // 4 channels for RGBA

        // Copy the red channel to all RGBA channels
        for (unsigned int row = 0; row < face->glyph->bitmap.rows; ++row) {
          for (unsigned int col = 0; col < face->glyph->bitmap.width; ++col) {
            unsigned char red = face->glyph->bitmap.buffer[row * face->glyph->bitmap.width + col];
            unsigned char* pixel = &rgbaBuffer[(row * face->glyph->bitmap.width + col) * 4]; // RGBA pixel
            pixel[0] = red; // Red channel
            pixel[1] = red; // Green channel
            pixel[2] = red; // Blue channel
            pixel[3] = (red == 0) ? 0 : 255; // Alpha channel (fully opaque)
          }
        }
 
        charList[i].size.x = face->glyph->bitmap.width;
        charList[i].size.y = face->glyph->bitmap.rows;
        charList[i].bearing.x = face->glyph->bitmap_left; // Conversion de la valeur en pixels
        charList[i].bearing.y = face->glyph->bitmap_top; // Conversion de la valeur en pixels
        // Load the glyph as GL_RGBA format
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBuffer.data());

        // Configuration des paramètres de texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
  }

    // Libérer les ressources FreeType
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

Texte::Texte(const char * nTexte,int glyphSize, const char* ttfPath)
  : pos(0.0f,0.0f),
    origin(0.0f,0.0f),
    rotation(0.0f),
    RGB(255,255,255),
    alpha(1.0f),
    texte(new char[strlen(nTexte) + 1]),
    sizeTexte(static_cast<unsigned int>(strlen(nTexte)+1)),
    glyphList(new NoTextureSprite[strlen(nTexte)+ 1]),
    offset(2.5f)
{
  strcpy(const_cast<char*>(texte), nTexte);
  sizeTexte = static_cast<unsigned int>(strlen(texte));
  loadFontTexture(ttfPath, glyphSize, charL, 128);
  buildTexte();
}

Texte::~Texte()
{
  delete [] glyphList;
  delete [] texte;
}

void Texte::buildTexte()
{
  float sizeTotal = 0.0f;
  for (unsigned int i = 0; i < sizeTexte; i++){
    glyphList[i].setSize(Vector2f(charL[texte[i]].size.x,charL[texte[i]].size.y));
    glyphList[i].setOrigin(Vector2f(-(sizeTotal+charL[texte[i]].bearing.x)+origin.x,charL[texte[i]].bearing.y+origin.y));
    glyphList[i].setPosition(pos);
    glyphList[i].setRotation(rotation);
    glyphList[i].setColor(RGB);
    glyphList[i].setAlpha(alpha);
    glyphList[i].setRGBFilterState(true);
    if(texte[i] == ' ')
      sizeTotal+=5.0f;
    sizeTotal+=charL[texte[i]].size.x+charL[texte[i]].bearing.x;
  }
}

void Texte::Draw(GLint renderModeLoc) const
{
  for (unsigned int i = 0; i < sizeTexte; i++){
    glBindTexture(GL_TEXTURE_2D, charL[texte[i]].TextureID);
    glyphList[i].Draw(renderModeLoc);
  }
}

Vector2f Texte::getPosition()
{
  return pos;
}

void Texte::setPosition(Vector2f nPos)
{
  pos = nPos;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setPosition(pos);
}

Vector2f Texte::getOrigin()
{
  return origin;
}

void Texte::setOrigin(Vector2f nOrigin)
{
  pos = nOrigin;
  float sizeTotal = 0.0f;
  for (unsigned int i = 0; i < sizeTexte; i++){
    glyphList[i].setOrigin(Vector2f(-(sizeTotal+charL[texte[i]].bearing.x)+origin.x,charL[texte[i]].bearing.y+origin.y));
    if(texte[i] == ' ')
      sizeTotal+=5.0f;
    sizeTotal+=charL[texte[i]].size.x+charL[texte[i]].bearing.x;
  }
}

Vector3i Texte::getColor()
{
  return RGB;
}

void Texte::setColor(Vector3i nRGB)
{
  RGB= nRGB;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setColor(RGB);
}

void Texte::setAlpha(float nAlpha)
{
  alpha = nAlpha;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setAlpha(alpha);
}

float Texte::getAlpha()
{
  return alpha;
}

void Texte::setRotation(float nRotation)
{
  rotation = nRotation;
  for (unsigned int i = 0; i < sizeTexte; i++)
    glyphList[i].setRotation(rotation);
}

float Texte::getRotation()
{
  return rotation;
}

void Texte::setTexte(const char * nTexte)
{
  delete [] texte;
  texte = new char[strlen(nTexte)+ 1];
  strcpy(const_cast<char*>(texte), nTexte);
  sizeTexte = static_cast<unsigned int>(strlen(texte));
  delete[] glyphList;
  glyphList = new NoTextureSprite[sizeTexte];
  buildTexte();
}

