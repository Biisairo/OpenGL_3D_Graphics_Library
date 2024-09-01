#version 430 core

uniform mat4 MODEL;

layout (std140binding = 0) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec3 VIEWPOS;
};

struct Light {
    uint emitType;
	// 0 directional light
	// 1 point light
	// 2 spot light

    vec3 position;
    vec3 color;

	float ambientStrength;
    float diffuseStrength;
    float specularStrength;

	// only for emitType 2, spotlight
	vec3 emitDirection;
	float innerCutoff;
    float outerCutoff;
};

layout (std430, binding = 0) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHTPOS[];
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 5) in vec3 aColor;

out Camera_VN_VS_OUT vs_out;

void main() {
	vs_out.VertexColor = aColor;
	
	vs_out.FragPos = vec3(MODEL * vec4(aPos, 1.0));   

	mat3 normalMatrix = transpose(inverse(mat3(MODEL)));

	vec3 N = normalize(normalMatrix * aNormal);
	vs_out.Normal = N;

	gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);
}