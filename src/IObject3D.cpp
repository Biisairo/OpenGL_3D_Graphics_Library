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
	if (child == nullptr)
		return;
		
	this->children.push_back(child);
	child->parent = this;
}

CGL::IObject3D* CGL::IObject3D::findChild(objectID ID) {
	if (this->getID() == ID)
		return this;
	
	for (std::vector<IObject3D*>::iterator it = this->children.begin(); it != this->children.end(); it++) {
		CGL::IObject3D* res = (*it)->findChild(ID);

		if (res)
			return res;
	}

	return nullptr;
}

CGL::IObject3D* CGL::IObject3D::removeChild(objectID ID) {
	if (this->getID() == ID)
		return this;

	CGL::IObject3D* target = this->findChild(ID);
	if (target == nullptr)
		return nullptr;
	
	CGL::IObject3D* targetParent = target->parent;
	for (std::vector<IObject3D*>::iterator it = targetParent->children.begin(); it != targetParent->children.end(); it++) {
		if (*it == target) {
			targetParent->children.erase(it);
		}
	}
	
	return target;
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

void CGL::IObject3D::addScale(glm::vec3 size) {
	glm::mat4 scaleDelta = glm::scale(glm::mat4(1), size);
	this->scale = scaleDelta * this->scale;
	this->model = this->translate * this->rotate * this->scale;
}

void CGL::IObject3D::setRotate(glm::vec3 axis, float angle) {
	this->rotate = glm::rotate(glm::mat4(1), angle, axis);
	this->model = this->translate * this->rotate * this->scale;
}

void CGL::IObject3D::addRotate(glm::vec3 axis, float angle) {
	glm::mat4 rotateDelta = glm::rotate(glm::mat4(1), angle, axis);
	this->rotate = rotateDelta * this->rotate;
	this->model = this->translate * this->rotate * this->scale;
}

void CGL::IObject3D::setTranslate(glm::vec3 pos) {
	this->translate = glm::translate(glm::mat4(1), pos);
	this->model = this->translate * this->rotate * this->scale;
}

void CGL::IObject3D::addTranslate(glm::vec3 pos) {
	glm::mat4 translateDelta = glm::translate(glm::mat4(1), pos);
	this->translate = translateDelta * this->translate;
	this->model = this->translate * this->rotate * this->scale;
}

glm::mat4& CGL::IObject3D::getModel() {
	return this->model;
}

CGL::ObjectType CGL::IObject3D::getObjectType() {
	return OBJECT_NONE;
}


// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////