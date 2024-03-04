#include "../../../include/BBOP/Graphics/shaders.h"

const char* defaultVertex = R"glsl(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection;

out vec4 outColor;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
    outColor = aColor;
    TexCoord = aTexCoord;
} 
)glsl";

const char* defaultFragment = R"glsl(
#version 330 core
out vec4 FragColor;
  
in vec4 outColor;
in vec2 TexCoord;

uniform sampler2D outTexture;
uniform vec4 ambiantLight;
uniform int renderMode;

void main()
{
  if (renderMode == 0){ 
    FragColor = texture(outTexture, TexCoord) * ambiantLight;
  } else if (renderMode == 1){
    FragColor = outColor * ambiantLight;
  } else if (renderMode == 2){
    FragColor = texture(outTexture, TexCoord) * outColor * ambiantLight;
  }
}
)glsl";

