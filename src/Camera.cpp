#include "Camera.hpp"

CGL::Camera::Camera(
	glm::vec3 position,
	glm::vec3 front,
	glm::vec3 up,

	float FoV,
	int width,
	int height,
	float zFar,
	float zNear,

	float moveSpeed,
	float mouseSpeed
) {
	this->FoV = FoV;
	this->width = width;
	this->height = height;
	this->zFar = zFar;
	this->zNear = zNear;

	this->position = position;
	this->front = glm::normalize(front);
	this->up = glm::normalize(up);
	this->right = glm::normalize(glm::cross(this->front, this->up));

	this->updateVectorWhenAngleBase();

	this->moveSpeed = moveSpeed;
	this->mouseSpeed = mouseSpeed;

	this->update();
}

CGL::Camera::Camera(
	glm::vec3 position,
	float horizontalAngle,
	float verticalAngle,

	float FoV,
	int width,
	int height,
	float zFar,
	float zNear,

	float moveSpeed,
	float mouseSpeed
) {
	this->FoV = FoV;
	this->width = width;
	this->height = height;
	this->zFar = zFar;
	this->zNear = zNear;

	this->position = position;

	this->horizontalAngle = horizontalAngle;
	this->verticalAngle = verticalAngle;

	this->updateVectorWhenAngleBase();

	this->moveSpeed = moveSpeed;
	this->mouseSpeed = mouseSpeed;

	this->update();
}

CGL::Camera::~Camera() {
	;
}

CGL::Camera::Camera(const Camera& other) : CGL::IObject3D(other) {
	this->FoV = other.FoV;
	this->width = other.width;
	this->height = other.height;
	this->zFar = other.zFar;
	this->zNear = other.zNear;

	this->position = other.position;
	this->front = other.front;
	this->right = other.right;
	this->up = other.up;

	this->update();
}

CGL::Camera& CGL::Camera::operator=(const Camera& other) {
	if (this != &other) {
		CGL:IObject3D::operator=(other);

		this->FoV = other.FoV;
		this->width = other.width;
		this->height = other.height;
		this->zFar = other.zFar;
		this->zNear = other.zNear;
		
		this->position = other.position;
		this->front = other.front;
		this->right = other.right;
		this->up = other.up;

		this->update();
	}

	return *this;
}


// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Camera::setViewRotate(glm::vec3 front) {

}

void CGL::Camera::addViewRotate(glm::vec3 axis, float angle) {
	glm::mat4 rotate = glm::rotate(glm::mat4(1), angle, axis);
	this->front = glm::normalize(rotate * glm::vec4(this->front, 0));
	this->right = glm::normalize(rotate * glm::vec4(this->right, 0));
	this->up = glm::normalize(rotate * glm::vec4(this->up, 0));

    this->updateAngleWhenVectorBase();

	this->update();

	this->addRotate(axis, angle);
}

void CGL::Camera::addViewRotate(float xDelta, float yDelta) {
    horizontalAngle += xDelta * this->mouseSpeed;
    verticalAngle -= yDelta * this->mouseSpeed;

    this->updateVectorWhenAngleBase();

	this->update();

    float yawAngle = xDelta * this->mouseSpeed;
    glm::vec3 yawAxis = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitchAngle = yDelta * this->mouseSpeed;
    glm::vec3 pitchAxis = this->right;

	glm::vec3 axis = glm::normalize(yawAxis + pitchAxis);
    float angle = glm::length(glm::vec2(yawAngle, pitchAngle));
	this->addRotate(axis, angle);
}

void CGL::Camera::setViewPosition(glm::vec3 position) {
	this->position = position;

	this->update();

	this->setTranslate(position);
}

void CGL::Camera::addViewPosition(glm::vec3 move) {
	this->position += move;

	this->update();

	this->addTranslate(move);
}

void CGL::Camera::addViewPosition(float xOffset, float yOffset, float zOffset) {
	this->position += this->front * zOffset * this->moveSpeed;
	this->position += this->right * xOffset * this->moveSpeed;
	this->position += this->up * yOffset * this->moveSpeed;

	this->update();

	this->addTranslate(glm::vec3(xOffset * this->moveSpeed, yOffset * this->moveSpeed, zOffset * this->moveSpeed));
}

CGL::ObjectType CGL::Camera::getObjectType() {
	return OBJECT_CAMERA;
}


// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Camera::update() {
	this->projection = glm::perspective(glm::radians(this->FoV), width / static_cast<float>(height), zNear, zFar);
	// this->projection = glm::ortho(0.f, (float)this->width, 0.f, (float)this->height, this->zNear, this->zFar);

	glm::vec3 center = glm::normalize(this->position + front);

	this->view = glm::lookAt(
		this->position,
		center,
		this->up
	);
}

void CGL::Camera::updateAngleWhenVectorBase() {
	this->verticalAngle = atan2(this->front.y, glm::length(glm::vec2(this->front.x, this->front.z)));
    this->horizontalAngle = atan2(this->front.z, this->front.x);;
}

void CGL::Camera::updateVectorWhenAngleBase() {
	if (this->verticalAngle > 89.0f) this->verticalAngle = 89.0f;
    if (this->verticalAngle < -89.0f) this->verticalAngle = -89.0f;

	this->front = glm::normalize(glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	));

    this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->front));

    this->up = glm::normalize(glm::cross(this->front, this->right));
}
