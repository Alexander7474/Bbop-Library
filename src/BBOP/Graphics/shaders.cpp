/*
 * shaders.cpp
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
// pixel de sortie du frag
out vec4 FragColor;

// info entrantes dans le fragshader depuis le vertexshader
in vec4 outColor;
in vec2 TexCoord;

// Permet de déterminer sir le shader doit render une texture, de la couluer ou les deux
uniform int renderMode;

// Texture a render quand rendermode vaut 0 ou 2
uniform sampler2D outTexture;

// Pixel de sortie du frag provisoire avant les calcule de la lumière
vec4 provisory;

void main()
{
  // coloration du pixel en fonction de rendermode
  if (renderMode == 0){ 
    provisory = texture(outTexture, TexCoord);
  } else if (renderMode == 1){
    provisory = outColor;
  } else if (renderMode == 2){
    provisory = texture(outTexture, TexCoord) * outColor;
  }
  
  //pixel final
  FragColor = provisory;
}

)glsl";


//LIGHT SHADER GLSL------------------------------------------------------------------------------------------------------------------------------------------------------

const char* lightVertex = R"glsl(
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

const char* lightFragment = R"glsl(
#version 330 core
// pixel de sortie du frag
out vec4 FragColor;

// info entrantes dans le fragshader depuis le vertexshader
in vec4 outColor;
in vec2 TexCoord;

// proj
uniform mat4 projectionCam;
uniform float camScale;

// lumière abiante
uniform vec4 ambiantLight;

// information général utile pour render envoyé par la class Scene
uniform vec2 windowSize;
uniform vec2 windowResolution;

// Texture a render quand rendermode vaut 0 ou 2
uniform sampler2D outTexture;

// Pixel de sortie du frag provisoire avant les calcule de la lumière
vec4 provisory;

// structure Light utiliser pour transmettre des lumières
struct Light { 
  vec2 pos; // Position de la source de lumière (2D)
  float intensity; // Intensité de la lumière
  float constantAttenuation; // Attnuation constante
  vec3 color; // Couleur de la lumière
  float linearAttenuation; // Attnuation linéaire
  float quadraticAttenuation; // Attnuation quadratique
  float rotationAngle;
  float openAngle;
};

// création d'une light
layout(std140) uniform LightsBlock {
  Light lights[100];
};
uniform int nLight;

// convertie des coordonnées en focntion de la résolution souhaité de la fenêtre
vec2 convertCoords(vec2 coord) 
{
  vec2 convertedCoords = coord;
  convertedCoords.x = (convertedCoords.x / windowSize.x) * windowResolution.x;
  convertedCoords.y = (convertedCoords.y / windowSize.y) * windowResolution.y;

  return convertedCoords;
}

// normalise des coordonnées entre 1 et -1 !!Attention a bien avoir convertie les coords
vec2 normalizeVec2(vec2 vector)
{
  vec2 normalized; 
  normalized.x = (vector.x / windowResolution.x) * 2.0 - 1.0;
  normalized.y = 1.0 - (vector.y / windowResolution.y) * 2.0;
  normalized.y = -normalized.y;
  return normalized;
}

void main()
{
  // texture du frame buffer
  provisory = texture(outTexture, TexCoord);

  //position du fragment actuelle
  vec2 convertedFrag = convertCoords(gl_FragCoord.xy);

  vec4 finalLight = ambiantLight;
  for (int i = 0; i < nLight; i++){

    //position de la light actuelle 
    vec4 lightPos = projectionCam * vec4(lights[i].pos, 0.0, 1.0);

    //déterminer si le fragment est dans le cône de lumière 
    vec2 lightDir = normalize(vec2(cos(lights[i].rotationAngle), sin(lights[i].rotationAngle))); // Direction de la lumière
    vec2 fragDir = normalize(normalizeVec2(convertedFrag) - lightPos.xy); // Direction du fragment vers la lumière
    float angleCos = dot(lightDir, fragDir); // Cosinus de l'angle entre les deux
    if (angleCos >= cos(lights[i].openAngle)) {
      // Le fragment est dans le cône
        ////disatnce entre la light et le fragment 
      float distance = length(lightPos.xy - normalizeVec2(convertedFrag)) * camScale;

      //attenuation en fonction de la distance et des différente valeur de la light 
      float attenuation = 1.0 / (lights[i].constantAttenuation + lights[i].linearAttenuation * distance + lights[i].quadraticAttenuation * distance * distance);

      //intensité de la light en fonction de son atténuation calculé 
      float intensity = attenuation*lights[i].intensity;

      //emballage dans un vec4
      vec4 thislight = intensity*vec4(lights[i].color, 0.0);
      finalLight+=thislight;
    }
  }

  //reset de l'alpha de la lumière(toujours 1.0 pour laisser l'alpha des texture et des shape seul déterminant de la transparence)
  finalLight.w = 1.0;

  //pixel final
  FragColor = provisory*finalLight;
}

)glsl";

