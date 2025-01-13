#include "ObjectCamera.hpp"

CGL::ObjectCamera::ObjectCamera(
	glm::vec3 position, // = glm::vec3(0, 0, 0),
	glm::vec3 front, // = glm::vec3(0, 0, -1),
	glm::vec3 up, // = glm::vec3(0, 1, 0),

	float fov,
	int width,
	int height,
	float zFar,
	float zNear
) : CGL::ICamera(position, front, up, fov, width, height, zFar, zNear) {
	;
}

CGL::ObjectCamera::ObjectCamera(
	glm::vec3 position, // = glm::vec3(0, 0, 0),
	float horizontalAngle, // = -glm::pi<float>(),
	float verticalAngle, // = 0.f,

	float fov,
	int width,
	int height,
	float zFar,
	float zNear
) : CGL::ICamera(position, horizontalAngle, verticalAngle, fov, width, height, zFar, zNear) {
	;
}

CGL::ObjectCamera::~ObjectCamera() {
	;
}

CGL::ObjectCamera::ObjectCamera(const CGL::ObjectCamera& other) : ICamera(other) {
	this->mouseSpeed = other.mouseSpeed;
	this->moveSpeed = other.mouseSpeed;
}

CGL::ObjectCamera& CGL::ObjectCamera::operator=(const CGL::ObjectCamera& other) {
	if (this != &other) {
		*this = other;
		this->mouseSpeed = other.mouseSpeed;
		this->moveSpeed = other.mouseSpeed;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::ObjectCamera::loopCamera(bool clickLeftMouse, bool clickRightMouse, double xDelta, double yDelta) {
	if (clickRightMouse) {
		this->addViewPosition(this->right * static_cast<float>(xDelta) * static_cast<float>(this->moveSpeed));
		this->addViewPosition(this->up * static_cast<float>(yDelta) * static_cast<float>(this->moveSpeed));
	}
	
	if (clickLeftMouse)
		this->addViewRotate(xDelta * mouseSpeed, yDelta * mouseSpeed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////