#include "../include/spriteClass.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void Sprite::buildVAO(){
  //construtiopn du VAO en fontion de la position du sprite, de  sa taille et de la taille de la fenetre
  // init sprite and texture coordinate ########################################
  //top right
  spriteVertices[0] = ((x+sizeX)/(windowX/2.0f))-1.0f; spriteVertices[1] = (-y/(windowY/2.0f))+1.0f;
  //botton right
  spriteVertices[8] = ((x+sizeX)/(windowX/2.0f))-1.0f; spriteVertices[9] = ((-y-sizeY)/(windowY/2.0f))+1.0f;
  //bottom left
  spriteVertices[16] = (x/(windowX/2.0f))-1.0f; spriteVertices[17] = ((-y-sizeY)/(windowY/2.0f))+1.0f;
  //top left
  spriteVertices[24] = (x/(windowX/2.0f))-1.0f; spriteVertices[25] = (-y/(windowY/2.0f))+1.0f;
  //texture coo
  spriteVertices[6] = 1.0f;spriteVertices[7] = 1.0f;spriteVertices[14] = 1.0f;spriteVertices[31] = 1.0f;
  spriteIndices[0] = 0;spriteIndices[1] = 1;spriteIndices[2] = 3;spriteIndices[3] = 1;spriteIndices[4] = 2;spriteIndices[5] = 3;
  spriteVAO.Bind();
  spriteVBO.update(spriteVertices, sizeof(spriteVertices));
  spriteEBO.update(spriteIndices, sizeof(spriteIndices));
  spriteVAO.LinkVBO(spriteVBO, 0, 3, 8, 0);
  spriteVAO.LinkVBO(spriteVBO, 1, 3, 8, 3);
  spriteVAO.LinkVBO(spriteVBO, 2, 2, 8, 6);
  spriteVAO.Unbind();
  spriteVBO.Unbind();
  spriteEBO.Unbind();
}

Sprite::Sprite(const char* textureFileName, GLFWwindow* win)
  : spriteShader("shaders/defaultTexture.vert", "shaders/defaultTexture.frag"),
    spriteVBO(spriteVertices, sizeof(spriteVertices)),
    spriteEBO(spriteIndices, sizeof(spriteIndices))
{
  for(int i = 0; i < (int)(sizeof(spriteVertices)/sizeof(GLfloat)); i++)
    spriteVertices[i] = 0.0f;
  for(int i = 0; i < (int)(sizeof(spriteIndices)/sizeof(GLuint)); i++)
    spriteIndices[i] = 0;
  spriteWindow = win;
  cout << "Creating sprite, image file: " << textureFileName << endl;
  cout << "-> VAO, VBO and EBO created" << endl;
  glGenTextures(1, &spriteTexture);
  glBindTexture(GL_TEXTURE_2D, spriteTexture);
  // définit les options de la texture actuellement liée
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // charge et génère la texture
  int textureWidth, textureHeight;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(textureFileName, &textureWidth, &textureHeight, &textureNrChannels, STBI_rgb_alpha);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    cout << "-> failed to load texture, loading default texture" << endl;
    textureFileName = "imgTesting/noTexture.png";
    data = stbi_load(textureFileName, &textureWidth, &textureHeight, &textureNrChannels, STBI_rgb_alpha);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
      cout << "-> failed to load default texture" << endl;
    }
  }
  stbi_image_free(data);
  cout << "-> texture loaded, size: " << textureWidth << "x" << textureHeight << endl;
  sizeX = (float)textureWidth; sizeY = (float)textureHeight;
  // Build du vao
  x = 0.0f;y = 0.0f;
  glfwGetWindowSize(spriteWindow, &windowX, &windowY);
  cout << "-> window size detected: " << windowX << "x" << windowY << endl;
  buildVAO();
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

void Sprite::setPosition(float nx, float ny){
  x = nx;y = ny; 
  //cout << x << ";" << y << endl;
  buildVAO();
}

float Sprite::getPositionX(){
  return x;
}

float Sprite::getPositionY(){
  return y;
}

void Sprite::setSize(float nSizeX, float nSizeY){
  sizeX = nSizeX;sizeY = nSizeY;
  buildVAO();
}

float Sprite::getSizeX(){
  return sizeX;
}

float Sprite::getSizeY(){
  return sizeY;
}
