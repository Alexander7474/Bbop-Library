#include "../../../include/BBOP/Graphics/textureClass.h"

using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
