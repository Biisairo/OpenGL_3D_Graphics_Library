#version 400 core

layout(location = 0) in vec3 VERTEX;
layout(location = 1) in vec3 aNORMAL;

out vec3 NORMAL;
out vec3 POS;

uniform mat4 MODEL;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
};

void main(){

	mat4 MVP = PROJECTION * VIEW * MODEL;
    gl_Position = MVP * vec4(VERTEX, 1);
	POS = vec3(MODEL * vec4(VERTEX, 1));
	NORMAL = mat3(transpose(inverse(MODEL))) * aNORMAL;
}

