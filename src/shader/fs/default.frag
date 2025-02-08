uniform sampler2D screenTexture;
out vec4 FragColor;

in vec2 TexCoords;

void main() {
    // FragColor = texture(screenTexture, TexCoords);

    float gamma = 2.2;
	FragColor = texture(screenTexture, TexCoords);
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
}