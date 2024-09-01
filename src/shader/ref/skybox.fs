#version 400 core

in vec3 TEXCOORD;

out vec4 color;

uniform samplerCube TEXTURE;

void main() {
	color = texture(TEXTURE, TEXCOORD);
}