#version 430 core

layout (std140binding = 0) uniform Matrices
{
    mat4 PROJECTION;
    mat4 VIEW;
	vec3 VIEWPOS;
};

layout (std430, binding = 0) uniform Lights
{
	uint LIGHT_COUNT;
	Light LIGHTPOS[];
};

int Camera_VN_VS_OUT fs_in;

out vec4 FragColor;

void main(){
    TangentSpace tangentSpace;

    tangentSpace.TBN = fs_in.TBN;
    tangentSpace.viewPos = fs_in.TBN * VIEWPOS;
    tangentSpace.fragPos = fs_in.TBN * fs_in * FragPos;
    tangentSpace.normal = fs_in.normal;

    for (int i = 0)
   
    // get diffuse color
    vec3 color = fs_in.VertexColor

    vec3 lightColorSum = vec3(0.0);
    for (int i = 0; i < LIGHT_COUNT; i++) {
        vec3 lightColor = computePointLight(LIGHT[i], tangentSpace);
        lightColorSum += lightColor;
    }
    
    color = color * lightColorSum;

    FragColor = vec4(ambient + diffuse + specular, fs_in.VertexColor.w);
}