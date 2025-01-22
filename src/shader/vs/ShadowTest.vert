out vec2 TexCoords;

void main() {
    // NDC 좌표 생성
    vec2 ndcPositions[4] = vec2[](
        vec2(-1.0, -1.0),
        vec2( 1.0, -1.0),
        vec2(-1.0,  1.0),
        vec2( 1.0,  1.0)
    );
    
    // 텍스처 좌표 생성
    vec2 texCoords[4] = vec2[](
        vec2(0.0, 0.0), // 좌측 하단
        vec2(1.0, 0.0), // 우측 하단
        vec2(0.0, 1.0), // 좌측 상단
        vec2(1.0, 1.0)  // 우측 상단
    );
    
    gl_Position = vec4(ndcPositions[gl_VertexID], 0.0, 1.0);
    TexCoords = texCoords[gl_VertexID];
}