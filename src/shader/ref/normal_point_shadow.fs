#version 400 core

in vec3 NORMAL;
in vec3 POSITION;

out vec4 color;

uniform vec3 COLOR;
uniform vec3 lightPos;
uniform float far_plane;
uniform vec3 VIEWPOS;

uniform samplerCube shadowMap;

vec3 sampleOffsetDirections[20] = vec3[]
(
    vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
    vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
    vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
    vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
    vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);  

float calcShadow(vec3 fragPos) {
    // vec3 fragToLight = fragPos - lightPos;
    // float closestDepth = texture(shadowMap, fragToLight).r;
    // closestDepth *= far_plane;
    // float currentDepth = length(fragToLight);

    // float bias = 0.05; 
    // float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;

    // vec3 fragToLight = fragPos - lightPos;
    // float currentDepth = length(fragToLight);
    // float shadow  = 0.0;
    // float bias    = 0.05; 
    // float samples = 4.0;
    // float offset  = 0.1;
    // for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    // {
    //     for(float y = -offset; y < offset; y += offset / (samples * 0.5))
    //     {
    //         for(float z = -offset; z < offset; z += offset / (samples * 0.5))
    //         {
    //             float closestDepth = texture(shadowMap, fragToLight + vec3(x, y, z)).r; 
    //             closestDepth *= far_plane;   // Undo mapping [0;1]
    //             if(currentDepth - bias > closestDepth)
    //                 shadow += 1.0;
    //         }
    //     }
    // }
    // shadow /= (samples * samples * samples);

    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);
    float shadow = 0.0;
    float bias   = 0.15;
    int samples  = 20;
    float viewDistance = length(VIEWPOS - fragPos);
    float diskRadius = (1.0 + (viewDistance / far_plane)) / 25.0;
    // float diskRadius = 0.01;
    for(int i = 0; i < samples; ++i)
    {
        float closestDepth = texture(shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
        closestDepth *= far_plane;
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);

    return shadow;
}

void main(){
    vec3 normal = normalize(NORMAL);
    vec3 lightDir = normalize(lightPos - POSITION);
    float light = max(dot(lightDir, normal), 0.0);

	float ambient = 0.1;

	float shadow = calcShadow(POSITION);

	color = vec4(COLOR * (light * (1.0 - shadow) + ambient), 1);
}