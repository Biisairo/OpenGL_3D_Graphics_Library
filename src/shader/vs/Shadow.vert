#include <common/CommonStruct.glsl>

uniform mat4 MODEL;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec4 VIEWPOS;
};

layout (std140) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHT[MAX_LIGHT_COUNT];
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec4 aColor;

void main()
{
    gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);
}  