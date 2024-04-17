/*
 * textureClass.cpp
 *
 * Ce programme est distribué sous les termes de la Licence Publique
 * Générale GNU, version 3.0, telle que publiée par la Free Software
 * Foundation. Consultez la Licence Publique Générale GNU pour plus de
 * détails.
 *
 * Vous devez avoir reçu une copie de la Licence Publique Générale GNU
 * en même temps que ce programme. Si ce n'est pas le cas, consultez
 * <https://www.gnu.org/licenses/>.
 */

#include "../../../include/BBOP/Graphics/textureClass.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace std;

Texture::Texture(const char* textureFileName){
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);
  // définit les options de la texture actuellement liée
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);
  // charge et génère la texture
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(textureFileName, &width, &height, &nrChannels, STBI_rgb_alpha);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
  }
  else
  {
    cerr << "BBOP ERROR -> failed to load texture" << endl;
  }
  stbi_image_free(data); 
  glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const Image &textureImage)
{
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);
  // définit les options de la texture actuellement liée
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);
  // charge et génère la texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width, textureImage.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage.data);
  glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() const
{
  return width;
}

int Texture::getHeight() const
{
  return height;
}

void Texture::Bind() const
{
  glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() const
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
  glDeleteTextures(1, &ID);
}

Image bbopLoadPartialImage(const char *filename, int nrChannels, int x, int y, int width, int height) {
    Image toLoad;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(filename, &toLoad.width, &toLoad.height, &toLoad.nrChannels, nrChannels);

    if (x + width > toLoad.width || y + height > toLoad.height) {
        stbi_image_free(data);
        toLoad.data = nullptr;
        return toLoad;
    }

    toLoad.data = (unsigned char *)malloc(width * height * nrChannels);
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            for (int k = 0; k < nrChannels; ++k) {
              toLoad.data[(j * width + i) * nrChannels + k] = data[((toLoad.height - y - height + j) * toLoad.width + (x + i)) * toLoad.nrChannels + k];
            }
        }
     }
    toLoad.width = width;
    toLoad.height = height;
    toLoad.nrChannels = nrChannels;

    stbi_image_free(data);
    return toLoad;
}

