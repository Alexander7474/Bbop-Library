#include "../../../include/BBOP/Graphics/fontsClass.h"
#include <vector>

// Charge une police TrueType en tant que texture OpenGL
void loadFontTexture(const char* fontPath, int fontSize, GLuint* textures, int numTextures) {
   
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

        // Inverser le glyph
        for (unsigned int row = 0; row < face->glyph->bitmap.rows / 2; ++row) {
          for (unsigned int col = 0; col < face->glyph->bitmap.width; ++col) {
            std::swap(face->glyph->bitmap.buffer[row * face->glyph->bitmap.width + col],
                      face->glyph->bitmap.buffer[(face->glyph->bitmap.rows - row - 1) * face->glyph->bitmap.width + col]);
          }
        }
        
        // Générer une texture OpenGL pour le glyphe
    
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);

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
