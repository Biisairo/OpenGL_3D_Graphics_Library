#include <common/CommonStruct.glsl>

layout (std140) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec4 VIEWPOS;
};

layout (std140) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHT[MAX_LIGHT_COUNT];
};

layout (std140) uniform Material
{
    vec4 AMBIENTCOLOR;
    vec4 DIFFUSECOLOR;
    vec4 SPECULARCOLOR;
    float ALPHA;
    float SHININESS;
};

out vec4 FragColor;

void main()
{
    FragColor = vec4(vec3(DIFFUSECOLOR), ALPHA);
}