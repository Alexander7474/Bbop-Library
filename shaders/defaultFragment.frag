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
