#version 430 core

uniform sampler2D diffuseMap;

in Camera_VT_VS_OUT fs_in;

out vec4 FragColor;

void main() {
	vec3 diffuseColor = texture(diffuseMap, fs_in.TexCoord).rgb;
	FragColor = fs_in.VertexColor * vec4(diffuseColor, 1.0);
}