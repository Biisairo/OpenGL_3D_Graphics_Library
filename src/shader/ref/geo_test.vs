#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec3 aColor;

out VS_OUT {
	vec3 normal;
} vs_out;

out vec3 POS;

uniform mat4 MODEL;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
};

void main(){

	mat4 MVP = PROJECTION * VIEW * MODEL;
    gl_Position = MVP * vec4(aPos, 1);

	POS = vec3(MODEL * vec4(aPos, 1));

	mat3 normalMat = mat3(transpose(inverse(VIEW * MODEL)));
	vs_out.normal = normalize(vec3(PROJECTION * vec4(normalMat * aNormal, 0.0)));
}

