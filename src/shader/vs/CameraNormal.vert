#include <common/CommonStruct.glsl>

// USE_NORMAL
// USE_TEXCOORD

uniform mat4 MODEL;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec4 VIEWPOS;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec4 aColor;

out Camera_VS_OUT {
	vec4 VertexColor;

    vec3 FragPos;
	vec3 Normal;

    vec2 TexCoords;

    mat4 TBN;
} vs_out;

// funtion

#if defined(USE_NORMAL) && defined(USE_TEXCOORD)
void CAMERA_VNT() {
    // init
    vs_out.VertexColor = vec4(0.0);
    vs_out.FragPos = vec3(0.0);
	vs_out.Normal = vec3(0.0);
    vs_out.TexCoords = vec2(0.0);
    vs_out.TBN = mat4(0.0);
    // init

    vs_out.VertexColor = aColor;

    vs_out.FragPos = vec3(MODEL * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
    
	// scale 이 normal 에 영향을 미치지 않도록 하기 위한 과정
    mat3 normalMatrix = transpose(inverse(mat3(MODEL)));

    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
	// TBN 행렬은 역행렬 == 전치행렬
    mat3 TBN = transpose(mat3(T, B, N));    

    vs_out.TBN = TBN;
	vs_out.Normal = N;
        
    gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);
}
#elif defined(USE_NORMAL)
void CAMERA_VN() {
	vs_out.VertexColor = aColor;
	
	vs_out.FragPos = vec3(MODEL * vec4(aPos, 1.0));   

	mat3 normalMatrix = transpose(inverse(mat3(MODEL)));

	vec3 N = normalize(normalMatrix * aNormal);
	vs_out.Normal = N;

	gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);
}
#elif defined(USE_TEXCOORD)
void CAMERA_VT() {
	vs_out.VertexColor = aColor;
	vs_out.TexCoord = aTexCoords;

	gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);
}
#else
void CAMERA_V() {
    vs_out.VertexColor = aColor;
    
	gl_Position = PROJECTION * VIEW * MODEL * vec4(aPos, 1.0);
}
#endif

// funtion

void main(){
    #if defined(USE_NORMAL) && defined(USE_TEXCOORD)
        CAMERA_VNT();
    #elif defined(USE_NORMAL)
        CAMERA_VN();
    #elif defined(USE_TEXCOORD)
        CAMERA_VT();
    #else
        CAMERA_V();
    #endif
}