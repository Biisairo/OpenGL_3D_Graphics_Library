#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "pch.hpp"

#include "IResourceID.hpp"
#include "Device.hpp"

enum ProjectionType {
	PROJECTION_PERSPECTIVE,
	PROJECTION_ORTHO
};

enum CenterType {
	CENTER_CAMERA,
	CENTER_OBJECT
};

class Camera : private IResourceID {
	private:
		Device* device;

		ProjectionType projectionType;
		CenterType centerType;

		glm::mat4 projection;

		float zFar;
		float zNear;

		glm::mat4 view;

		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 front;

		int width;
		int height;

		float horizontalAngle;
		float verticalAngle;
		float FoV;

	public:
		Camera() = delete;
		Camera(Device* device, int width, int height, ProjectionType projection_type, CenterType center_type);
		~Camera();

		void update();

		glm::mat4 getProjection();
		glm::mat4 getView();

		void updateUniform();
};

#endif