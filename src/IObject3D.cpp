#include "IObject3D.hpp"

CGL::IObject3D::IObject3D() {
	this->parent = nullptr;
	this->initModel();
}

CGL::IObject3D::~IObject3D() {
}

CGL::IObject3D::IObject3D(const IObject3D &other) : CGL::IResourceID(other) {
	this->parent = nullptr;

	this->model = other.model;
	this->scale = other.scale;
	this->rotate = other.rotate;
	this->translate = other.translate;
}

CGL::IObject3D& CGL::IObject3D::operator=(const IObject3D &other) {
	if (this != &other) {
		CGL:IResourceID::operator=(other);

		this->parent = nullptr;

		this->model = other.model;
		this->scale = other.scale;
		this->rotate = other.rotate;
		this->translate = other.translate;
	}
    
	return *this;
}


// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::IObject3D::setParent(IObject3D *parent) {
	this->parent = parent;
}

CGL::IObject3D* CGL::IObject3D::getParent() {
	return this->parent;
}

void CGL::IObject3D::addChild(IObject3D *child) {
	this->children.push_back(child);
}

CGL::IObject3D* CGL::IObject3D::removeChild(unsigned int ID) {
	for (std::vector<IObject3D*>::iterator it = this->children.begin(); it != this->children.end(); it++) {
		if ((*it)->getID() == ID) {
			CGL::IObject3D* curIObject3D = *it;
			this->children.erase(it);
			return curIObject3D;
		}
	}

	return nullptr;
}

std::vector<CGL::IObject3D*>& CGL::IObject3D::getChildren() {
	return this->children;
}


void CGL::IObject3D::initModel() {
	this->model = glm::mat4(1);
	this->scale = glm::mat4(1);
	this->rotate = glm::mat4(1);
	this->translate = glm::mat4(1);
}

void CGL::IObject3D::setScale(glm::vec3 size) {
	this->scale = glm::scale(glm::mat4(1), size);
	this->model = this->translate * this->rotate * this->scale;
}

void CGL::IObject3D::setRotate(float angle, glm::vec3 axis) {
	this->rotate = glm::rotate(glm::mat4(1), angle, axis);
	this->model = this->translate * this->rotate * this->scale;
}

void CGL::IObject3D::setTranslate(glm::vec3 pos) {
	this->translate = glm::translate(glm::mat4(1), pos);
	this->model = this->translate * this->rotate * this->scale;
}

glm::mat4& CGL::IObject3D::getModel() {
	return this->model;
}


// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////