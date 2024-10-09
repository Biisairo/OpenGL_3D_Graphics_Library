#ifndef COMMON_STRUCT_GLSL
#define COMMON_STRUCT_GLSL

struct Light {
	uint emitType;
	// 0 directional light
	// 1 point light
	// 2 spot light

	float ambientStrength;
	float diffuseStrength;
	float specularStrength;

	vec4 ambientcolor;
	vec4 diffusecolor;
	vec4 specularcolor;

	// 강도
	float intensity;

	// 감쇄 상수
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
	// (1 / constant + linear × d + quadratic × d x d), d 는 거리

	// multiple minus when directional light
	vec4 position;

	// only for emitType 2, spotlight
	vec4 emitDirection;
	float innerCutoff;
	float outerCutoff;

	// padding
	float padding[2];
};

struct TangentSpace {
	mat4 TBN;
	vec3 normal;

	vec3 fragPos;
	vec3 viewPos;
};

#endif