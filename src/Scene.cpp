#include "Scene.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGL::Scene::Scene() {
	// this->root = nullptr;
	this->mainCamera = nullptr;
}

CGL::Scene::~Scene() {
	;
}

// CGL::Scene::Scene(const CGL::Scene& other) {
// 	;
// }

// CGL::Scene& CGL::Scene::operator=(const CGL::Scene& other) {
// 	if (this != &other) {
// 		;
// 	}

// 	return *this;
// }

CGL::IObject3D* CGL::Scene::getRoot() {
	return &this->root;
}

void CGL::Scene::addObject(CGL::IObject3D* object) {
	this->root.addChild(object);
}

CGL::IObject3D* CGL::Scene::findObject(objectID ID) {
	return this->root.findChild(ID);
}

CGL::IObject3D* CGL::Scene::removeObject(objectID ID) {
	return this->root.removeChild(ID);
}

void CGL::Scene::setMainCamera(Camera* mainCamera) {
	this->mainCamera = mainCamera;
}

CGL::Camera* CGL::Scene::getMainCamera() {
	return this->mainCamera;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////