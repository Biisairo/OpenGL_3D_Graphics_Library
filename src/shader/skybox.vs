#version 400 core

layout(location = 0) in vec3 VERTEX;

out vec3 TEXCOORD;

uniform mat4 MODEL;
uniform mat4 SKYBOXVIEW;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
};

void main() {
	mat4 MVP = PROJECTION * SKYBOXVIEW * MODEL;
	gl_Position = (MVP * vec4(VERTEX, 1)).xyww;
	TEXCOORD = VERTEX;
}