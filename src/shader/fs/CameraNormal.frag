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
	vec4 VIEWPOS;
};

layout (std140) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHT[MAX_LIGHT_COUNT];
};

layout (std140) uniform Material
{
    vec4 AMBIENTCOLOR;
    vec4 DIFFUSECOLOR;
    vec4 SPECULARCOLOR;
    float ALPHA;
    float SHININESS;
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

vec4 computeLight(Light light, TangentSpace tangentSpace) {
    vec4 lightColor = vec4(0.0);

    // 빛 방향 및 거리 계산
    vec3 lightDir;
    float distance = length(light.position.xyz - tangentSpace.fragPos); // 거리 계산
    float attenuation;

    if (light.emitType == 0) { // Directional Light

        lightDir = normalize(-light.emitDirection.xyz);
        attenuation = 1.0; // Directional light는 거리 감쇠가 없음

    } else if (light.emitType == 1) { // Point Light

        lightDir = normalize(light.position.xyz - tangentSpace.fragPos);

        // 거리 감쇠
        attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));

    } else if (light.emitType == 2) { // Spot Light

        lightDir = normalize(light.position.xyz - tangentSpace.fragPos);
        float spotEffect = dot(lightDir, normalize(-light.emitDirection.xyz));

        float innerCutoff = cos(light.innerCutoff);
        float outerCutoff = cos(light.outerCutoff);

        // 거리 감쇠
        attenuation;

        if (spotEffect < outerCutoff) { // 스포트라이트 범위 밖에 있는 경우

            attenuation = 0;

        } else if (spotEffect < innerCutoff) { // 스포트라이트 범위 중간에 있는 경우

            // 비율을 구하고 clamping하여 0.0에서 1.0 사이로 설정
            float spotEffectAdjusted = (spotEffect - outerCutoff) / (innerCutoff - outerCutoff);
            spotEffectAdjusted = clamp(spotEffectAdjusted, 0.0, 1.0);
            
            // 기존의 distance attenuation에 스포트 효과를 곱하여 적용
            attenuation = spotEffectAdjusted / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));

        } else { // 스포트 라이트 내부에 있는 경우

            attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * distance + light.quadraticAttenuation * (distance * distance));
        
        }

    }

    // Phong 모델을 사용한 조명 계산
    vec3 normal = normalize(tangentSpace.normal);
    float diffuseStrength = max(dot(normal, lightDir), 0.0);

    vec3 viewDir = normalize(tangentSpace.viewPos - tangentSpace.fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SHININESS); // 물체의 shininess 특성 사용

    lightColor += attenuation * (
        light.ambientStrength * light.ambientcolor * AMBIENTCOLOR+
        diffuseStrength * light.diffuseStrength * light.diffusecolor  * DIFFUSECOLOR +
        spec * light.specularStrength * light.specularcolor * SPECULARCOLOR
    );

    return lightColor; // 최종 조명 색상 반환
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
        tangentSpace.viewPos = VIEWPOS.xyz;
        tangentSpace.fragPos = fs_in.FragPos;
        tangentSpace.normal = fs_in.Normal;
    #endif

    // get diffuse color
    vec3 fragColor = fs_in.VertexColor.xyz;
    #if defined(USE_DIFFUSE_MAP) && defined(USE_TEXCOORD)
        fragColor = texture(diffuseMap, fs_in.TexCoords).rgb * fs_in.VertexColor;
    #endif

    vec4 lightColorSum = vec4(1.0);
    #if defined(USE_NORMAL)
    if (LIGHT_COUNT > 0) {
        lightColorSum = vec4(0.0);
        for (int i = 0; i < LIGHT_COUNT; i++) {
            vec4 lightColor = computeLight(LIGHT[i], tangentSpace);
            lightColorSum += lightColor;
        }
    }
    #endif
    
    FragColor = vec4(fragColor * lightColorSum.xyz, ALPHA);
}