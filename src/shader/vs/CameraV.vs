#version 430 core

uniform mat4 MODEL;

layout (std140binding = 0) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec3 VIEWPOS;
};

layout (location = 0) in vec3 aPos;
layout (location = 5) in vec3 aColor;

out Camera_V_VS_OUT vs_out;

void main() {
    vs_out.VertexColor = aColor;
    
	gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);

}