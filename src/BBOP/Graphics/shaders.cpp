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
uniform vec2 windowSize;
uniform vec2 windowResolution;

vec4 provisory;

vec2 convertCoords(vec2 coord) 
{
  vec2 convertedCoords = coord;
  convertedCoords.x = (convertedCoords.x / windowSize.x) * windowResolution.x;
  convertedCoords.y = (convertedCoords.y / windowSize.y) * windowResolution.y;

  return convertedCoords;
}

vec2 normalizeVec2(vec2 vector)
{
  vec2 normalized; 
  normalized.x = (vector.x / windowResolution.x) * 2.0 - 1.0;
  normalized.y = 1.0 - (vector.y / windowResolution.y) * 2.0;
  normalized.y = -normalized.y;
  return normalized;
}


const vec2 lightPosition = vec2(200.0, 800.0); // Position de la source de lumière (2D)
const vec3 lightColor = vec3(1.0, 1.0, 1.0); // Couleur de la lumière
const float lightIntensity = 0.2; // Intensité de la lumière

const float constantAttenuation = 0.1; // Attnuation constante
const float linearAttenuation = 1.1; // Attnuation linéaire
const float quadraticAttenuation = 0.1; // Attnuation quadratique

void main()
{
  if (renderMode == 0){ 
    provisory = texture(outTexture, TexCoord);
  } else if (renderMode == 1){
    provisory = outColor;
  } else if (renderMode == 2){
    provisory = texture(outTexture, TexCoord) * outColor;
  }
  
  vec2 convertedFrag = convertCoords(gl_FragCoord.xy);
  float distance = length(normalizeVec2(lightPosition) - normalizeVec2(convertedFrag));
  float attenuation = 1.0 / (constantAttenuation + linearAttenuation * distance + quadraticAttenuation * distance * distance);
  float intensity = ambiantLight.x+(attenuation*lightIntensity);
  vec4 finalLight = intensity*vec4(lightColor, 1.0);

  FragColor = provisory*finalLight;
}

)glsl";

