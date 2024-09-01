#version 400 core
layout (location = 0) in vec3 VERTEX;

uniform mat4 MODEL;

void main()
{
    gl_Position = MODEL * vec4(VERTEX, 1.0);
}