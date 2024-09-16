#include "Scene.hpp"

CGL::Scene::Scene() {
	this->root = nullptr;
	this->mainCameraID = 0;
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

void CGL::Scene::addObject(IObject3D* object) {
	this->root->addChild(object);
}

void CGL::Scene::removeObject(objectID ID) {
	this->root->removeChild(ID);
}

void CGL::Scene::setMainCamera(objectID mainCameraID) {
	this->mainCameraID = mainCameraID;
}


// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////




// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////