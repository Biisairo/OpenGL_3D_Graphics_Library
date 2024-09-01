#version 430 core

uniform sampler2D diffuseMap;

#ifdef NORMAL_MAPPING
uniform sampler2D normalMap;
#endif

#ifdef HEIGHT_MAPPING
uniform sampler2D depthMap;
uniform float heightScale;
#endif


layout (std140binding = 0) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec3 VIEWPOS;
};

layout (std430, binding = 0) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHT[];
};

int Camera_VNT_VS_OUT fs_in;

out vec4 FragColor;

void main(){
    TangentSpace tangentSpace;
    tangentSpace.TBN = fs_in.TBN;
    tangentSpace.viewPos = fs_in.TBN * VIEWPOS;
    tangentSpace.fragPos = fs_in.TBN * fs_in.FragPos;

    vec2 texCoord = fs_in.TexCoords;
    #ifdef HEIGHT_MAPPING
        vec3 viewDir = normalize(ftangentSpace.viewPos - tangentSpace.fragPos);
        texCoord = parallaxMapping(viewDir, fs_in.TexCoords, depthMap, heightScale);
    #endif

    vec3 normal = fs_in.Normal;
    #ifdef NORMAL_MAPPING
        // obtain normal from normal map in range [0,1]
        normal = texture(normalMap, texCoord).rgb;
        // transform normal vector to range [-1,1]
        normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
    #endif

    tangentSpace.normal = normal;

    // get diffuse color
    vec3 color = texture(diffuseMap, fs_in.TexCoords).rgb;
    color = color * fs_in.VertexColor;

    vec3 lightColorSum = vec3(0.0);
    for (int i = 0; i < LIGHT_COUNT; i++) {
        vec3 lightColor = computePointLight(LIGHT[i], tangentSpace);
        lightColorSum += lightColor;
    }
    
    color = color * lightColorSum;

    FragColor = vec4(ambient + diffuse + specular, fs_in.VertexColor.w);
}