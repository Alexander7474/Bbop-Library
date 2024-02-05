#include "../include/spriteClass.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Sprite::Sprite(const char* textureFileName, GLFWwindow* win)
  : spriteShader("shaders/defaultTexture.vert", "shaders/defaultTexture.frag")
{
  spriteWindow = win;
  cout << "Creating sprite, image file: " << textureFileName << endl;
  glGenTextures(1, &spriteTexture);
  glBindTexture(GL_TEXTURE_2D, spriteTexture);
  // définit les options de la texture actuellement liée
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // charge et génère la texture
  stbi_set_flip_vertically_on_load(true);
  int width, height, nrChannels;
  unsigned char *data = stbi_load(textureFileName, &width, &height, &nrChannels, STBI_rgb_alpha);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    cout << "-> failed to load texture, loading default texture" << endl;
    textureFileName = "imgTesting/noTexture.png";
    data = stbi_load(textureFileName, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      cout << "-> failed to load default texture" << endl;
    }
  }
  stbi_image_free(data);
  cout << "-> texture loaded" << endl;
  int windowX, windowY;
  glfwGetWindowSize(spriteWindow, &windowX, &windowY);
  cout << "-> window size detected: " << windowX << "x" << windowY << endl;
  GLfloat vertices[] = {
    // positions          // colors           // texture coords
     0.2f,  0.2f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom left
    -0.2f,  0.2f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 1.0f    // top left 
  };
  //copy dans la variable privé de sprite
  copy(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]), spriteVertices);
  GLuint spriteIndices[] =
  {
    0, 1, 3,   // premier triangle
    1, 2, 3    // second triangle
  };
  spriteVAO.Bind();
  VBO spriteVBO(spriteVertices, sizeof(spriteVertices));
  EBO spriteEBO(spriteIndices, sizeof(spriteIndices));
  cout << "-> VAO, VBO and EBO created" << endl;
  spriteVAO.LinkVBO(spriteVBO, 0, 3, 8, 0);
  spriteVAO.LinkVBO(spriteVBO, 1, 3, 8, 3);
  spriteVAO.LinkVBO(spriteVBO, 2, 2, 8, 6);
  spriteVAO.Unbind();
  spriteVBO.Unbind();
  spriteEBO.Unbind();
  cout << "-> VBO and EBO linked to VAO" << endl;
  cout << "-> sprite with " << textureFileName << " created" << endl;
}

void Sprite::Draw() 
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  spriteShader.Activate();
  glBindTexture(GL_TEXTURE_2D, spriteTexture);
  spriteVAO.Bind();  
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
