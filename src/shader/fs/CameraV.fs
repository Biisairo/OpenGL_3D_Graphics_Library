#version 430 core

in Camera_V_VS_OUT fs_in;

out vec4 FragColor;

void main() {
	FragColor = fs_in.VertexColor;
}