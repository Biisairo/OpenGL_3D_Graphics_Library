#version 400 core

layout(location = 0) in vec3 VERTEX;
layout(location = 1) in vec3 aNORMAL;

uniform mat4 MODEL;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
};

out vec3 NORMAL;
out vec3 POSITION;

void main(){

	mat4 MVP = PROJECTION * VIEW * MODEL;
	gl_Position = MVP * vec4(VERTEX, 1);

	NORMAL = transpose(inverse(mat3(MODEL))) * aNORMAL;

	POSITION = vec3(MODEL * vec4(VERTEX, 1));
}

