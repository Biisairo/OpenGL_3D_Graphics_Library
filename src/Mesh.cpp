#include "Mesh.hpp"

Mesh::Mesh(Device* device, Mesh *parent) {
	this->device = device;

	this->modelInit();

	this->parent = parent;
	if (this->parent != nullptr)
		this->parent->addChild(this);

    this->needUpdate = false;
}

Mesh::~Mesh() {
	for (int i = 0; i < this->children.size(); i++) {
		delete this->children[i];
	}

	this->device->deleteMesh(this->getID());
}

void Mesh::addChild(Mesh* child) {
	this->children.push_back(child);
}

void Mesh::setPosition (std::vector<glm::vec3> &position) {
    this->needUpdate = true;

	this->position = position;
}

void Mesh::setNormal (std::vector<glm::vec3> &normal) {
    this->needUpdate = true;

	this->normal = normal;
}

void Mesh::setTexCoords (std::vector<glm::vec2> &texCoords) {
    this->needUpdate = true;

	this->texCoords = texCoords;
}

void Mesh::setTangent (std::vector<glm::vec3> &tangent) {
    this->needUpdate = true;

	this->tangent = tangent;
}

void Mesh::setBitangent (std::vector<glm::vec3> &bitangent) {
    this->needUpdate = true;

	this->bitangent = bitangent;
}

void Mesh::setColors (std::vector<glm::vec4> &colors) {
    this->needUpdate = true;

	this->colors = colors;
}

void Mesh::setColors (glm::vec4 &color) {
    this->needUpdate = true;

	this->colors.clear();
	this->colors.push_back(color);
}

void Mesh::setIndex (std::vector<GLuint> &index) {
    this->needUpdate = true;

	this->index = index;
}


void Mesh::modelInit() {
	this->model = glm::mat4(1);
	this->scaleMat = glm::mat4(1);
	this->rotateMat = glm::mat4(1);
	this->translateMat = glm::mat4(1);
}

void Mesh::setInstancing(std::vector<glm::mat4> &instancing) {
	this->instancing = instancing;
}

void Mesh::setScale(glm::vec3 size) {
	this->scaleMat = glm::scale(glm::mat4(1), size);
	this->model = this->translateMat * this->rotateMat * this->scaleMat;
}

void Mesh::setRotate(float angle, glm::vec3 axis) {
	this->rotateMat = glm::rotate(glm::mat4(1), angle, axis);
	this->model = this->translateMat * this->rotateMat * this->scaleMat;
}

void Mesh::setTranslate(glm::vec3 pos) {
	this->translateMat = glm::translate(glm::mat4(1), pos);
	this->model = this->translateMat * this->rotateMat * this->scaleMat;
}

glm::mat4& Mesh::getModel() {
	return this->model;
}

MeshDTO Mesh::getMeshDTO() {
    return {
        this->getID(), 
        this->position,
        this->normal,
        this->texCoords,
        this->tangent,
        this->bitangent,
        this->colors,
        this->index
    };
}

void Mesh::drawMesh() {
    if (this->needUpdate) {
        this->updateBuffer();
        this->needUpdate = false;
    }
    
    this->device->draw(this->getID(), this->model, DRAW_TRIANGLES);
}

void Mesh::drawLine() {
    if (this->needUpdate) {
        this->updateBuffer();
        this->needUpdate = false;
    }
    
    this->device->draw(this->getID(), this->model, DRAW_LINE);
}

void Mesh::drawPoint() {
    if (this->needUpdate) {
        this->updateBuffer();
        this->needUpdate = false;
    }
    
    this->device->draw(this->getID(), this->model, DRAW_POINT);
}

void Mesh::setVertexData() {
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

	if (this->position.size() != this->colors.size() && this->colors.size() == 1) {
		glm::vec4 color;
		if (this->colors.size() == 0)
			color = glm::vec4(1, 1, 1, 1);
		else
			glm::vec4 color = this->colors.front();
		this->colors.clear();
		
		for (int i = 0; i < position.size(); i++)
			this->colors.push_back(color);
	}
}

void Mesh::makeNormal() {
    // 정점의 법선을 초기화하고 크기를 설정
    this->normal.resize(this->position.size(), glm::vec3(0.0f));
    std::vector<int> counts(this->position.size(), 0);

    // 각 삼각형에 대해 법선을 계산하고 정점에 누적
    for (int i = 0; i < this->index.size() / 3; i++) {
        uint idx0 = this->index[i * 3 + 0];
        uint idx1 = this->index[i * 3 + 1];
        uint idx2 = this->index[i * 3 + 2];

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

void Mesh::makeTangentSpace() {
    this->tangent.resize(this->position.size(), glm::vec3(0.0f));
    this->bitangent.resize(this->position.size(), glm::vec3(0.0f));
    std::vector<int> counts(this->position.size(), 0);

    for (int i = 0; i < this->index.size() / 3; i++) {
        uint idx0 = this->index[i * 3 + 0];
        uint idx1 = this->index[i * 3 + 1];
        uint idx2 = this->index[i * 3 + 2];

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

void Mesh::updateBuffer() {
    this->setVertexData();

    this->device->updateMesh(
        this->getMeshDTO()
    );
}