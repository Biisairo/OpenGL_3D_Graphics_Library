#ifndef COMMON_STRUCT_GLSL
#define COMMON_STRUCT_GLSL

struct Camera_VS_OUT {
	vec4 VertexColor;

    vec3 FragPos;
	vec3 Normal;

    vec2 TexCoords;

    mat4 TBN;
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

struct TangentSpace {
	mat4 TBN;
	vec3 normal;

	vec3 fragPos;
	vec3 viewPos;
};

#endif