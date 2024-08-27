#include "Mesh.hpp"

Mesh::Mesh(Device* device, Mesh *parent) {
	this->device = device;

	this->modelInit();

	this->parent = parent;
	if (this->parent != nullptr)
		this->parent->addChild(this);
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

void Mesh::setVertex(std::vector<glm::vec3> &vertex) {
	this->vertex = vertex;
}

void Mesh::setIndex(std::vector<uint> &index) {
	this->index = index;
}

void Mesh::setNormal(std::vector<glm::vec3> &normal) {
	this->normal = normal;
}

void Mesh::setUV(std::vector<glm::vec2> &UV) {
	this->UV = UV;
}

void Mesh::setColor(glm::vec4 color) {
	this->color = color;
}

void Mesh::modelInit() {
	this->model = glm::mat4(1);
	this->scaleMat = glm::mat4(1);
	this->rotateMat = glm::mat4(1);
	this->translateMat = glm::mat4(1);
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

// parameter 를 수정한 뒤 수동으로 호출할 것
void Mesh::updateBuffer() {
	std::vector<glm::vec3> alignedVertex;
	for (int i = 0; i < this->index.size() / 3; i++)
	{
		int idx0 = index[i * 3 + 0];
		int idx1 = index[i * 3 + 1];
		int idx2 = index[i * 3 + 2];

		alignedVertex.push_back(this->vertex[idx0]);
		alignedVertex.push_back(this->vertex[idx1]);
		alignedVertex.push_back(this->vertex[idx2]);
	}

	this->device->updateMesh(
		this->getID(), 
		alignedVertex,
		this->normal,
		this->UV
	);
}

void Mesh::test() {
	std::cout << this->getID() << std::endl;
}