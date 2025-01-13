#include "PlayerCamera.hpp"

CGL::PlayerCamera::PlayerCamera(
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

CGL::PlayerCamera::PlayerCamera(
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

CGL::PlayerCamera::~PlayerCamera() {
	;
}

CGL::PlayerCamera::PlayerCamera(const CGL::PlayerCamera& other) : ICamera(other) {
	this->mouseSpeed = other.mouseSpeed;
	this->moveSpeed = other.mouseSpeed;
}

CGL::PlayerCamera& CGL::PlayerCamera::operator=(const CGL::PlayerCamera& other) {
	if (this != &other) {
		*this = other;
		this->mouseSpeed = other.mouseSpeed;
		this->moveSpeed = other.mouseSpeed;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::PlayerCamera::loopCamera(float delta, bool moveUp, bool moveDown, bool moveLeft, bool moveRight, double xDelta, double yDelta) {
	if (moveUp)
		this->addViewPosition(0, 0, delta * this->moveSpeed);
	if (moveDown)
		this->addViewPosition(0, 0, -delta * this->moveSpeed);
	if (moveRight)
		this->addViewPosition(delta * this->moveSpeed, 0, 0);
	if (moveLeft)
		this->addViewPosition(-delta * this->moveSpeed, 0, 0);
	
	this->addViewRotate(xDelta * mouseSpeed, yDelta * mouseSpeed);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////