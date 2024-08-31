#version 400 core
layout (location = 0) in vec3 VERTEX;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
};
uniform mat4 MODEL;

void main()
{
    gl_Position = PROJECTION * VIEW * MODEL * vec4(VERTEX, 1.0);
}  