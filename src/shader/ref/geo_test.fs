#version 400 core

in vec4 fcolor;

out vec4 color;

void main()
{
    // color = vec4(1.0, 1.0, 0.0, 1.0);
    color = fcolor;
}  