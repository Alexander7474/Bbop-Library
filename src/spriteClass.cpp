#include "../include/spriteClass.h"

#include <stb/stb_image.h>

Sprite::Sprite(const char* textureFileName, int sizeX, int sizeY)
  : spriteShader("shaders/defaultTexture.vert", "shaders/defaultTexture.frag")
{
  glGenTextures(1, &spriteTexture);
  glBindTexture(GL_TEXTURE_2D, spriteTexture);
  // définit les options de la texture actuellement liée
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // charge et génère la texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load(textureFileName, &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    cout << "Failed to load texture, loading default texture" << endl;  
    unsigned char *data2 = stbi_load("../imgTesting/noTexture.png", &width, &height, &nrChannels, 0);
    if (data2)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      cout << "Failed to load default texture" << endl;
    }
  }
  stbi_image_free(data);
  GLfloat spriteVertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f    // top left 
  };
  GLuint spriteIndices[] =
  {
    0, 1, 3,   // premier triangle
    1, 2, 3    // second triangle
  };
  spriteVAO.Bind();
  VBO spriteVBO(spriteVertices, sizeof(spriteVertices));
  EBO spriteEBO(spriteIndices, sizeof(spriteIndices));
  spriteVAO.LinkVBO(spriteVBO, 0, 3, 8, 0);
  spriteVAO.LinkVBO(spriteVBO, 1, 3, 8, 3);
  spriteVAO.LinkVBO(spriteVBO, 2, 2, 8, 6);
  spriteVAO.Unbind();
  spriteVBO.Unbind();
  spriteEBO.Unbind(); 
}

void Sprite::Draw() 
{
  spriteShader.Activate();
  glBindTexture(GL_TEXTURE_2D, spriteTexture);
  spriteVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
