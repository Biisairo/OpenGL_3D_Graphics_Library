#include <common/CommonStruct.glsl>

// USE_NORMAL
// USE_TEXCOORD

// USE_DIFFUSE_MAP
// USE_NORMAL_MAP
// USE_HEIGHT_MAP

uniform sampler2D diffuseMap;

uniform sampler2D normalMap;

uniform sampler2D heightMap;
uniform float heightScale;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec4 VIEWPOS;
};

layout (std140) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHT[10];
};

out vec4 FragColor;

in vec4 FragPos;

void main()
{
    vec3 ratio = (FragPos.xyz + vec3(1, 1, 1)) / 2;
    FragColor = vec4(ratio, 1);
}