#version 400 core

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D DIFFUSE1;
uniform sampler2D SPECULAR1;
uniform sampler2D HEIGHT1;

uniform float height_scale;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    float height =  texture(HEIGHT1, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * height_scale);
    return texCoords - p;    
}

vec2 SteepParallaxMapping(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float layer = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir))); 

    float layerDepth = 1.0 / layer;
    float currentLayerDepth = 0.0;

    vec2 p = viewDir.xy * height_scale;
    vec2 deltaTexCoords = p / layer;

    vec2  currentTexCoords = texCoords;
    float currentHEIGHT1Value = texture(HEIGHT1, currentTexCoords).r;
    
    while(currentLayerDepth < currentHEIGHT1Value)
    {
        currentTexCoords -= deltaTexCoords;
        currentHEIGHT1Value = texture(HEIGHT1, currentTexCoords).r;  
        currentLayerDepth += layerDepth;  
    }

    return currentTexCoords;
}

vec2 ParallaxOcclusionMapping(vec2 texCoords, vec3 viewDir)
{
    const float minLayers = 8.0;
    const float maxLayers = 32.0;
    float layer = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir))); 

    float layerDepth = 1.0 / layer;
    float currentLayerDepth = 0.0;

    vec2 p = viewDir.xy * height_scale;
    vec2 deltaTexCoords = p / layer;

    vec2  currentTexCoords = texCoords;
    float currentHEIGHT1Value = texture(HEIGHT1, currentTexCoords).r;
    
    while(currentLayerDepth < currentHEIGHT1Value)
    {
        currentTexCoords -= deltaTexCoords;
        currentHEIGHT1Value = texture(HEIGHT1, currentTexCoords).r;  
        currentLayerDepth += layerDepth;  
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    float afterDepth  = currentHEIGHT1Value - currentLayerDepth;
    float beforeDepth = texture(HEIGHT1, prevTexCoords).r - currentLayerDepth + layerDepth;
    
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords; 
}

void main(){
    vec3 viewDir   = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    // vec2 texCoords = ParallaxOcclusionMapping(fs_in.TexCoords,  viewDir);
    // if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
    //     discard;
    vec2 texCoords = fs_in.TexCoords;

    vec3 normal = texture(HEIGHT1, texCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec3 color = texture(DIFFUSE1, texCoords).rgb;
    vec3 ambient = 0.1 * color;
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specMap = texture(SPECULAR1, texCoords).rgb;

    // vec3 specular = vec3(0.2) * spec;
    vec3 specular = specMap * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);

    // FragColor = texture(DIFFUSE1, texCoords);

    // FragColor = vec4(1, 1, 1, 1);

    // FragColor = texture(DIFFUSE1, fs_in.TexCoords);
    // FragColor = texture(NORMAL1, fs_in.TexCoords);
    // FragColor = texture(HEIGHT1, fs_in.TexCoords);
}