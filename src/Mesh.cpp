#include "Mesh.hpp"

CGL::Mesh::Mesh() {
	needToUpdate = false;
}

CGL::Mesh::~Mesh() {
	;
}

CGL::Mesh::Mesh(const CGL::Mesh& other) : IObject3D(other) {
	this->needToUpdate = other.needToUpdate;

	this->position = other.position;
	this->normal = other.normal;
	this->texCoords = other.texCoords;
	this->tangent = other.tangent;
	this->bitangent = other.bitangent;
	this->colors = other.colors;
	this->index = other.index;

	this->material = other.material;
}

CGL::Mesh& CGL::Mesh::operator=(const CGL::Mesh& other) {
	if (this != &other) {
		CGL:IObject3D::operator=(other);

		this->needToUpdate = other.needToUpdate;

		this->position = other.position;
		this->normal = other.normal;
		this->texCoords = other.texCoords;
		this->tangent = other.tangent;
		this->bitangent = other.bitangent;
		this->colors = other.colors;
		this->index = other.index;

		this->material = other.material;
	}

	return *this;
}


// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Mesh::setPosition(std::vector<glm::vec3>& position) {
    this->needToUpdate = true;

	this->position = position;
}

void CGL::Mesh::setNormal(std::vector<glm::vec3>& normal) {
    this->needToUpdate = true;

	this->normal = normal;
}

void CGL::Mesh::setTexCoords(std::vector<glm::vec2>& texCoords) {
    this->needToUpdate = true;

	this->texCoords = texCoords;
}

void CGL::Mesh::setTangent(std::vector<glm::vec3>& tangent) {
    this->needToUpdate = true;

	this->tangent = tangent;
}

void CGL::Mesh::setBitangent(std::vector<glm::vec3>& bitangent) {
    this->needToUpdate = true;

	this->bitangent = bitangent;
}

void CGL::Mesh::setColors(std::vector<glm::vec4>& colors) {
    this->needToUpdate = true;

	this->colors = colors;
}

void CGL::Mesh::setColors(glm::vec4& color) {
    this->needToUpdate = true;

	this->colors.clear();
	this->colors.push_back(color);
}

void CGL::Mesh::setIndex(std::vector<indice>& index) {
    this->needToUpdate = true;

	this->index = index;
}

void CGL::Mesh::setMaterial(CGL::Material& material) {
	this->needToUpdate = true;

	this->material = material;
}

CGL::ObjectType CGL::Mesh::getObjectType() {
	return OBJECT_MESH;
}


// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Mesh::setVertexData() {
	if (this->needToUpdate == false)
		return;

	if (this->position.size() == 0)
		return;

	this->needToUpdate = false;

	if (this->position.size() != this->normal.size()) {
		this->makeNormal();
	}
	
	if (this->position.size() != this->texCoords.size()) {
		this->texCoords.clear();
		this->tangent.clear();
		this->bitangent.clear();
	} else if (this->position.size() != this->tangent.size() ||
		this->position.size() != this->bitangent.size()) {
		this->makeTangentSpace();
	}

	if (this->position.size() != this->colors.size()) {
		glm::vec4 color;
		if (this->colors.size() == 1)
			glm::vec4 color = this->colors.front();
		else
			color = glm::vec4(1, 1, 1, 1);
		this->colors.clear();
		
		for (int i = 0; i < position.size(); i++)
			this->colors.push_back(color);
	}
}

void CGL::Mesh::makeNormal() {
    // 정점의 법선을 초기화하고 크기를 설정
    this->normal.resize(this->position.size(), glm::vec3(0.0f));
    std::vector<int> counts(this->position.size(), 0);

    // 각 삼각형에 대해 법선을 계산하고 정점에 누적
    for (int i = 0; i < this->index.size() / 3; i++) {
        indice idx0 = this->index[i * 3 + 0];
        indice idx1 = this->index[i * 3 + 1];
        indice idx2 = this->index[i * 3 + 2];

        glm::vec3 pos0 = this->position[idx0];
        glm::vec3 pos1 = this->position[idx1];
        glm::vec3 pos2 = this->position[idx2];

        // 삼각형의 두 변을 구함
        glm::vec3 edge0 = pos1 - pos0;
        glm::vec3 edge1 = pos2 - pos0;

        // 법선 벡터는 두 벡터의 외적(cross product)으로 계산
        glm::vec3 normal = glm::normalize(glm::cross(edge0, edge1));

        // 정점별로 법선 벡터를 누적
        this->normal[idx0] += normal;
        this->normal[idx1] += normal;
        this->normal[idx2] += normal;

        counts[idx0]++;
        counts[idx1]++;
        counts[idx2]++;
    }

    // 누적된 법선 벡터를 정규화하여 최종 법선을 얻음
    for (int i = 0; i < this->position.size(); i++) {
        if (counts[i] > 0) {
            this->normal[i] = glm::normalize(this->normal[i] / (float)counts[i]);
        }
    }
}

void CGL::Mesh::makeTangentSpace() {
    this->tangent.resize(this->position.size(), glm::vec3(0.0f));
    this->bitangent.resize(this->position.size(), glm::vec3(0.0f));
    std::vector<int> counts(this->position.size(), 0);

    for (int i = 0; i < this->index.size() / 3; i++) {
        indice idx0 = this->index[i * 3 + 0];
        indice idx1 = this->index[i * 3 + 1];
        indice idx2 = this->index[i * 3 + 2];

        glm::vec3 pos0 = this->position[idx0];
        glm::vec3 pos1 = this->position[idx1];
        glm::vec3 pos2 = this->position[idx2];

        glm::vec2 uv0 = this->texCoords[idx0];
        glm::vec2 uv1 = this->texCoords[idx1];
        glm::vec2 uv2 = this->texCoords[idx2];

        glm::vec3 edge0 = pos1 - pos0;
        glm::vec3 edge1 = pos2 - pos0;
        glm::vec2 deltaUV0 = uv1 - uv0;
        glm::vec2 deltaUV1 = uv2 - uv0;

        float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

        glm::vec3 tangent;
        tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
        tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
        tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);

        glm::vec3 bitangent;
        bitangent.x = f * (-deltaUV1.x * edge0.x + deltaUV0.x * edge1.x);
        bitangent.y = f * (-deltaUV1.x * edge0.y + deltaUV0.x * edge1.y);
        bitangent.z = f * (-deltaUV1.x * edge0.z + deltaUV0.x * edge1.z);

        // 정점별로 탄젠트와 비탄젠트 누적
        this->tangent[idx0] += tangent;
        this->tangent[idx1] += tangent;
        this->tangent[idx2] += tangent;

        this->bitangent[idx0] += bitangent;
        this->bitangent[idx1] += bitangent;
        this->bitangent[idx2] += bitangent;

        counts[idx0]++;
        counts[idx1]++;
        counts[idx2]++;
    }

    // 각 정점의 탄젠트와 비탄젠트를 평균화 및 정규화
    for (int i = 0; i < this->position.size(); i++) {
        if (counts[i] > 0) {
            glm::vec3& t = this->tangent[i];
            glm::vec3& b = this->bitangent[i];
            glm::vec3& n = this->normal[i];

            // 탄젠트와 비탄젠트를 평균화 및 정규화
            t = glm::normalize(t / (float)counts[i]);
            b = glm::normalize(b / (float)counts[i]);

            // 탄젠트 벡터가 노멀 벡터와 직교하도록 보정
            t = glm::normalize(t - glm::dot(t, n) * n);

            // 비탄젠트 벡터가 노멀과 탄젠트 벡터 모두와 직교하도록 보정 (그램-슈미트 정규화)
            b = glm::normalize(b - glm::dot(b, n) * n - glm::dot(b, t) * t);
        }
    }
}