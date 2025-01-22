uniform sampler2D screenTexture;
uniform bool PERSPECTIVE;
out vec4 FragColor;

in vec2 TexCoords;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * 0.1 * 100) / (100 + 0.1 - z * (100 - 0.1));
}

void main() {
    float depthValue = texture(screenTexture, TexCoords).r;
    if (PERSPECTIVE)
        FragColor = vec4(vec3(LinearizeDepth(depthValue) / 100.0), 1.0); // perspective
    else
        FragColor = vec4(vec3(depthValue / 2), 1.0); // orthographic
}