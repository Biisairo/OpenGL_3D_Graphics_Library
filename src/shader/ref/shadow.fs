#version 400 core
out vec4 color;
  
in vec2 TEXCOR;

uniform sampler2D TEXTURE;

void main()
{             
    float depthValue = texture(TEXTURE, TEXCOR).r;
    color = vec4(vec3(depthValue), 1.0);
} 