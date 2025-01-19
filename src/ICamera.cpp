#include "ICamera.hpp"

CGL::ICamera::ICamera(
	glm::vec3 position,
	glm::vec3 front,
	glm::vec3 up,

	float fov,
	int width,
	int height,
	float zFar,
	float zNear
) {
	this->fov = fov;
	this->width = width;
	this->height = height;
	this->zFar = zFar;
	this->zNear = zNear;

	this->position = position;
	this->front = glm::normalize(front);
	this->up = glm::normalize(up);
	this->right = glm::normalize(glm::cross(this->front, this->up));

	this->updateVectorWhenAngleBase();

	this->update();
}

CGL::ICamera::ICamera(
	glm::vec3 position,
	float horizontalAngle,
	float verticalAngle,

	float fov,
	int width,
	int height,
	float zFar,
	float zNear
) {
	this->fov = fov;
	this->width = width;
	this->height = height;
	this->zFar = zFar;
	this->zNear = zNear;

	this->position = position;

	this->horizontalAngle = horizontalAngle;
	this->verticalAngle = verticalAngle;

	this->updateVectorWhenAngleBase();

	this->update();
}

CGL::ICamera::~ICamera() {
	;
}

CGL::ICamera::ICamera(const ICamera& other) : CGL::IObject3D(other) {
	this->fov = other.fov;
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

CGL::ICamera& CGL::ICamera::operator=(const ICamera& other) {
	if (this != &other) {
		CGL:IObject3D::operator=(other);

		this->fov = other.fov;
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::ICamera::setViewRotate(glm::vec3 front) {
    this->front = glm::normalize(front);
    this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->front));
    this->up = glm::normalize(glm::cross(this->front, this->right));

	this->updateAngleWhenVectorBase();

	this->update();

    glm::vec3 defaultFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 axis = glm::normalize(glm::cross(defaultFront, this->front));
    float angle = acos(glm::dot(defaultFront, this->front));

    this->setRotate(axis, angle);
}

void CGL::ICamera::addViewRotate(glm::vec3 axis, float angle) {
	glm::mat4 rotate = glm::rotate(glm::mat4(1), angle, axis);
	this->front = glm::normalize(rotate * glm::vec4(this->front, 0));
	this->right = glm::normalize(rotate * glm::vec4(this->right, 0));
	this->up = glm::normalize(rotate * glm::vec4(this->up, 0));

    this->updateAngleWhenVectorBase();

	this->update();

	this->addRotate(axis, angle);
}
void CGL::ICamera::addViewRotate(float xDelta, float yDelta) {
	float originalHorizontalAngle = this->horizontalAngle;
	float originalVerticalAngle = this->verticalAngle;

    horizontalAngle += xDelta;
    verticalAngle += yDelta;

    this->updateVectorWhenAngleBase();

	this->update();

	float realXDelta = this->horizontalAngle - originalHorizontalAngle;
	float realYDelta = this->verticalAngle - originalVerticalAngle;

	this->addRotate(glm::vec3(0, 1, 0), realXDelta);
	this->addRotate(this->right, -realYDelta);
}

void CGL::ICamera::setViewPosition(glm::vec3 position) {
	this->position = position;

	this->update();

	this->setTranslate(position);
}

void CGL::ICamera::addViewPosition(glm::vec3 move) {
	this->position += move;

	this->update();

	this->addTranslate(move);
}

void CGL::ICamera::addViewPosition(float xOffset, float yOffset, float zOffset) {
	this->position += this->front * zOffset;
	this->position -= this->right * xOffset;
	this->position += this->up * yOffset;

	this->update();

	this->setTranslate(this->position);
}

glm::mat4 CGL::ICamera::getProjection() {
	return this->projection;
}

glm::mat4 CGL::ICamera::getView() {
	return this->view;
}

glm::vec4 CGL::ICamera::getViewPos() {
	return glm::vec4(this->position, 1);
}

CGL::ObjectType CGL::ICamera::getObjectType() {
	return OBJECT_CAMERA;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::ICamera::update() {
	if (this->fov < 0)
		this->projection = glm::ortho(0.f, (float)this->width, 0.f, (float)this->height, this->zNear, this->zFar);
	else
		this->projection = glm::perspective(this->fov, static_cast<float>(this->width) / static_cast<float>(this->height), zNear, zFar);

	glm::vec3 center = this->position + this->front;

	this->view = glm::lookAt(
		this->position,
		center,
		this->up
	);

	if (this->getParent() != nullptr) {
		glm::mat4 parentModel = this->getParent()->getModel();
		this->view = glm::inverse(parentModel) * this->view;
	}
}

void CGL::ICamera::updateAngleWhenVectorBase() {
	this->verticalAngle = atan2(this->front.y, glm::length(glm::vec2(this->front.x, this->front.z)));
    this->horizontalAngle = atan2(this->front.z, this->front.x);;
}

void CGL::ICamera::updateVectorWhenAngleBase() {
	float vAngleDegree = glm::degrees(this->verticalAngle);

	if (vAngleDegree > 89.9)
		vAngleDegree = 89.9;
    if (vAngleDegree < -89.9)
		vAngleDegree = -89.9;

	this->verticalAngle = glm::radians(vAngleDegree);

	this->front = glm::normalize(glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	));

    this->right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->front));

    this->up = glm::normalize(glm::cross(this->front, this->right));
}
