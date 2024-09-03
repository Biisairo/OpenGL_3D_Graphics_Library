#ifndef COMMON_FUNCTION_GLSL
#define COMMON_FUNCTION_GLSL

vec3 computePointLight(Lights light, TangentSpace tangentSpace) {
	vec3 tangentLightPos = tangentSpace.TBN * light.position;

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

vec2 simpleParallaxMapping(vec2 texCoords, vec3 viewDir, sampler2D depthMap, float heightScale)
{ 
    float height =  texture(depthMap, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * heightScale);
    return texCoords - p;    
}

vec2 steepParallaxMapping(vec2 texCoords, vec3 viewDir, sampler2D depthMap, float heightScale)
{
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float layer = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir))); 

    float layerDepth = 1.0 / layer;
    float currentLayerDepth = 0.0;

    vec2 p = viewDir.xy * heightScale;
    vec2 deltaTexCoords = p / layer;

    vec2  currentTexCoords = texCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;
    
    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;  
        currentLayerDepth += layerDepth;  
    }

    return currentTexCoords;
}

vec2 parallaxOcclusionMapping(vec2 texCoords, vec3 viewDir, sampler2D depthMap, float heightScale)
{
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float layer = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir))); 

    float layerDepth = 1.0 / layer;
    float currentLayerDepth = 0.0;

    vec2 p = viewDir.xy * heightScale;
    vec2 deltaTexCoords = p / layer;

    vec2  currentTexCoords = texCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;
    
    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;  
        currentLayerDepth += layerDepth;  
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;
    
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords; 
}

vec2 parallaxMapping(vec3 viewDir, vec2 texCoord, sampler2D depthMap, float heightScale) {
    vec2 resTexCoord = parallaxOcclusionMapping(texCoord,  viewDir, depthMap, heightScale);
    if(resTexCoord.x > 1.0 || resTexCoord.y > 1.0 || resTexCoord.x < 0.0 || resTexCoord.y < 0.0)
        discard;
	
	return resTexCoord;
}

#endif