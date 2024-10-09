#include <common/CommonStruct.glsl>

// USE_NORMAL
// USE_TEXCOORD

uniform mat4 MODEL;

// uniform mat4 PROJECTION;
// uniform mat4 VIEW;
// uniform vec4 VIEWPOS;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec4 VIEWPOS;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec4 aColor;

out vec4 FragPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    FragPos = gl_Position;
}