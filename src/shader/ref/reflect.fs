#version 400 core

in vec3 POS;
in vec3 NORMAL;

out vec4 color;

uniform samplerCube TEXTURE;
uniform vec3 CAMPOS;

void main(){
	float ratio = 1 / 2.42;
	vec3 i = normalize(POS - CAMPOS);
	vec3 r = reflect(i, normalize(NORMAL));
	// vec3 r = refract(i, normalize(NORMAL), ratio);

	color = vec4(texture(TEXTURE, r).rgb, 1);
}