#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "pch.hpp"

#include "IResourceID.hpp"
#include "CommonStructure.hpp"
#include "CommonEnum.hpp"
#include "Device.hpp"

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

		CameraDTO getCameraDTO();

		void updateUniform();
};

#endif