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

vec4 provisory;

const vec2 lightPosition = vec2(0.5, 0.5); // Position de la source de lumière (2D)
const vec3 lightColor = vec3(1.0, 1.0, 1.0); // Couleur de la lumière
const float lightIntensity = 5.0; // Intensité de la lumière

const float constantAttenuation = 0.1; // Attnuation constante
const float linearAttenuation = 0.1; // Attnuation linéaire
const float quadraticAttenuation = 0.01; // Attnuation quadratique

void main()
{
  if (renderMode == 0){ 
    provisory = texture(outTexture, TexCoord) * ambiantLight;
  } else if (renderMode == 1){
    provisory = outColor * ambiantLight;
  } else if (renderMode == 2){
    provisory = texture(outTexture, TexCoord) * outColor * ambiantLight;
  }

  float distance = length(lightPosition - gl_FragCoord.xy);
  float attenuation = 1.0 / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);
  float intensity = lightIntensity * attenuation;

  FragColor = provisory*intensity;
}
)glsl";

