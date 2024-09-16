#include <iostream>

#include "Mesh.hpp"
#include "Camera.hpp"

int main() {
	CGL::IObject3D* root = new CGL::IObject3D();

	CGL::IObject3D* meshTest = new CGL::Mesh();
	CGL::IObject3D* cameraTest = new CGL::Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	root->addChild(meshTest);
	root->addChild(cameraTest);

	objectID tmpID;

	for (int i = 0; i < 10; i++) {
		CGL::IObject3D* mesh = new CGL::Mesh();
		meshTest->addChild(mesh);
	}
	for (int i = 0; i < 10; i++) {
		CGL::IObject3D* camera = new CGL::Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		if (i == 5)
			tmpID = camera->getID();

		cameraTest->addChild(camera);
	}

	std::cout << "tmpID : " << tmpID << std::endl;

	CGL::IObject3D* temp = root->findChild(tmpID);

	std::cout << "temp id : " << temp->getID() << std::endl;
}