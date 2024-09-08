#include <common/CommonStruct.glsl>

// USE_NORMAL
// USE_TEXCOORD

// USE_DIFFUSE_MAP
// USE_NORMAL_MAP
// USE_HEIGHT_MAP

uniform sampler2D diffuseMap;

uniform sampler2D normalMap;

uniform sampler2D heightMap;
uniform float heightScale;

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec3 VIEWPOS;
};

layout (std140) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHT[10];
};

in Camera_VS_OUT {
	vec4 VertexColor;

    vec3 FragPos;
	vec3 Normal;

    vec2 TexCoords;

    mat4 TBN;
} fs_in;

out vec4 FragColor;

// funtion

vec3 computePointLight(Light light, TangentSpace tangentSpace) {
	vec3 tangentLightPos = (tangentSpace.TBN * vec4(light.position, 1.0)).xyz;

	// ambient
    float ambient = light.ambientStrength;

    // diffuse
    vec3 lightDir = normalize(tangentLightPos - tangentSpace.fragPos);
    float diff = max(dot(lightDir, tangentSpace.normal), 0.0);
    float diffuse = diff * light.diffuseStrength;

    // specular
    vec3 viewDir = normalize(tangentSpace.viewPos - tangentSpace.fragPos);
    vec3 reflectDir = reflect(-lightDir, tangentSpace.normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float specular = pow(max(dot(tangentSpace.normal, halfwayDir), 0.0), light.specularStrength);

	float weight = ambient + diffuse + specular;

	vec3 lightColor = weight * light.color;

	return lightColor;
}

vec2 parallaxOcclusionMapping(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float layer = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir))); 

    float layerHeight = 1.0 / layer;
    float currentLayerHeight = 0.0;

    vec2 p = viewDir.xy * heightScale;
    vec2 deltaTexCoords = p / layer;

    vec2  currentTexCoords = texCoords;
    float currentHeightMapValue = texture(heightMap, currentTexCoords).r;
    
    while(currentLayerHeight < currentHeightMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentHeightMapValue = texture(heightMap, currentTexCoords).r;  
        currentLayerHeight += layerHeight;  
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    float afterHeight  = currentHeightMapValue - currentLayerHeight;
    float beforeHeight = texture(heightMap, prevTexCoords).r - currentLayerHeight + layerHeight;
    
    float weight = afterHeight / (afterHeight - beforeHeight);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords; 
}

vec2 parallaxMapping(vec3 viewDir, vec2 texCoord) {
    vec2 resTexCoord = parallaxOcclusionMapping(texCoord,  viewDir);
    if(resTexCoord.x > 1.0 || resTexCoord.y > 1.0 || resTexCoord.x < 0.0 || resTexCoord.y < 0.0)
        discard;
	
	return resTexCoord;
}

// funtion

void main(){
    TangentSpace tangentSpace;
    tangentSpace.TBN = mat4(1.0);
    #if defined(USE_NORMAL) && defined(USE_TEXCOORD)
        tangentSpace.TBN = fs_in.TBN;
        tangentSpace.viewPos = fs_in.TBN * VIEWPOS;
        tangentSpace.fragPos = fs_in.TBN * fs_in.FragPos;

        vec2 texCoord = fs_in.TexCoords;
        #if defined(USE_HEIGHT_MAP)
            vec3 viewDir = normalize(tangentSpace.viewPos - tangentSpace.fragPos);
            texCoord = parallaxMapping(viewDir, fs_in.TexCoords);
        #endif

        mat3 normalMatrix = transpose(mat3(tangentSpace.TBN));
        vec3 normal = normalize(normalMatrix * fs_in.Normal);
        #if defined(USE_NORMAL_MAP)
            // obtain normal from normal map in range [0,1]
            normal = texture(normalMap, texCoord).rgb;
            // transform normal vector to range [-1,1]
            normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
        #endif

        tangentSpace.normal = normal;
    #elif defined(USE_NORMAL)
        tangentSpace.viewPos = VIEWPOS;
        tangentSpace.fragPos = fs_in.FragPos;
        tangentSpace.normal = fs_in.Normal;
    #endif

    // get diffuse color
    vec3 fragColor = fs_in.VertexColor.xyz;
    #if defined(USE_DIFFUSE_MAP) && defined(USE_TEXCOORD)
        fragColor = texture(diffuseMap, fs_in.TexCoords).rgb * fs_in.VertexColor;
    #endif

    vec3 lightColorSum = vec3(1.0);
    #if defined(USE_NORMAL)
    lightColorSum = vec3(0.0);
    for (int i = 0; i < LIGHT_COUNT; i++) {
        vec3 lightColor = vec3(0);
        if (LIGHT[i].emitType == 0) {
            ;
        } else if (LIGHT[i].emitType == 1) {
            lightColor = computePointLight(LIGHT[i], tangentSpace);
        } else if (LIGHT[i].emitType == 2) {
            ;
        }
        lightColorSum += lightColor;
    }
    #endif
    
    vec3 colorWithLight = fragColor * lightColorSum;

    FragColor = vec4(colorWithLight, fs_in.VertexColor.w);
}