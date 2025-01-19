#include <common/CommonStruct.glsl>

uniform mat4 MODEL;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec4 VIEWPOS;
};

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1);
}