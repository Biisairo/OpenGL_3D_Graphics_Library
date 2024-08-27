#include "Camera.hpp"

Camera::Camera(Device* device, int width, int height, ProjectionType projection_type, CenterType center_type) {
	this->device = device;

	this->projectionType = projection_type;
	this->centerType = center_type;

	this->FoV = 45.0f;
	this->width = width;
	this->height = height;
	this->zFar = 1000.f;
	this->zNear = 0.1f;
	this->position = glm::vec3(0, 0, 0);
	this->up = glm::vec3(0, 1, 0);
	this->horizontalAngle = 0;
	this->verticalAngle = 0;
}

Camera::~Camera() {
	this->device->deleteCamera(this->getID());
}

void Camera::update() {
	if (this->projectionType == PROJECTION_PERSPECTIVE)
		this->projection = glm::perspective(glm::radians(this->FoV), width / static_cast<float>(height), zNear, zFar);
	else if (this->projectionType == PROJECTION_ORTHO)
		this->projection = glm::ortho(0.f, (float)this->width, 0.f, (float)this->height, this->zNear, this->zFar);

	// 카메라가 보고있는 방향
	this->front = glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// right vector
	this->right = glm::vec3(
		sin(horizontalAngle - glm::radians(90.f)), 
		0,
		cos(horizontalAngle - glm::radians(90.f))
	);

	// 카메라가 보고있는 방향에서 y축을 무시한 것
	// {
	// 	glm::vec3 front_no_y(
	// 		sin(horizontalAngle),
	// 		0,
	// 		cos(horizontalAngle)
	// 	);
		
	// 	glm::vec3 UP_no_y = glm::cross(this->right, front_no_y);
	// }
	
	this->up = glm::cross(this->right, front);

	glm::vec3 center = this->position + this->front;

	this->view = glm::lookAt(
		this->position,
		center,
		this->up
	);
}

glm::mat4 Camera::getProjection() {
	return this->projection;
}

glm::mat4 Camera::getView() {
	return this->view;
}

void Camera::updateUniform() {
	this->device->updateCamera(this->getID());
}