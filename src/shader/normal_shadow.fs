#version 400 core

in vec3 NORMAL;
in vec4 FragPosLightSpace;

out vec4 color;

uniform vec3 COLOR;
uniform vec3 lightPos;

uniform sampler2D shadowMap;

float calcShadow(vec4 fragPosLightSpace) {
	// float bias = 0.005;
	float bias = max(0.05 * (1.0 - dot(NORMAL, lightPos)), 0.005); 
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	// float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
	float shadow = 0.0;
	
    if(projCoords.z > 1.0)
        return shadow;

	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;

	return shadow;
}

void main(){
	float light = max(dot(NORMAL, lightPos), 0.0);
	float ambient = 0.1;

	float shadow = calcShadow(FragPosLightSpace);
	color = vec4(COLOR * (light * (1.0 - shadow) + ambient), 1);
}