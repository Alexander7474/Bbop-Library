#include "../../../include/BBOP/Graphics/textureClass.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char* textureFileName){
  cout << "Creating Texture " << textureFileName << endl;
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);
  // définit les options de la texture actuellement liée
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // charge et génère la texture
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(textureFileName, &width, &height, &nrChannels, STBI_rgb_alpha);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
  }
  else
  {
    cout << "-> failed to load texture, loading default texture" << endl;
    textureFileName = "imgTesting/noTexture.png";
    data = stbi_load(textureFileName, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else
    {
      cout << "-> failed to load default texture" << endl;
    }
  }
  stbi_image_free(data); 
}

int Texture::getWidth()
{
  return width;
}

int Texture::getHeight()
{
  return height;
}

void Texture::Bind() const
{
  glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
  glDeleteTextures(1, &ID);
}
