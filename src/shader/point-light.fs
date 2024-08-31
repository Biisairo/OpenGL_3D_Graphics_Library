#version 400 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);
    lightDistance = lightDistance / far_plane; // 깊이를 0-1 로 정규화
    gl_FragDepth = lightDistance;
}