#include "../../../include/BBOP/Graphics/shaders.h"

const char* defaultVertex = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    outColor = aColor;
    TexCoord = aTexCoord;
} 
)glsl";

const char* defaultFragment = R"glsl(
#version 330 core
out vec4 FragColor;
  
in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D outTexture;
uniform vec4 ambiantLight;
uniform int renderMode;

void main()
{
  if (renderMode == 0){ 
    FragColor = texture(outTexture, TexCoord) * ambiantLight;
  } else if (renderMode == 1){
    FragColor = vec4(outColor, 1.0) * ambiantLight;
  } else if (renderMode == 2){
    FragColor = texture(outTexture, TexCoord) * vec4(outColor, 1.0) * ambiantLight;
  }
}
)glsl";

