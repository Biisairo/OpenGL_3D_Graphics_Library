#ifndef PLAYER_CAMERA_HPP
#define PLAYER_CAMERA_HPP

#include "Extern/OpenGLHeader.hpp"
#include "Extern/GLMHeader.hpp"

#include "ICamera.hpp"
#include "Device.hpp"

namespace CGL {

	class PlayerCamera : public ICamera {
		private:
			double mouseSpeed = 0.001;
			double moveSpeed = 10;

		public:
			PlayerCamera() = delete;
			PlayerCamera(
				glm::vec3 position, // = glm::vec3(0, 0, 0),
				glm::vec3 front, // = glm::vec3(0, 0, -1),
				glm::vec3 up, // = glm::vec3(0, 1, 0),

				float fov = glm::radians(45.f),
				int width = 800,
				int height = 600,
				float zFar = 1000.f,
				float zNear = 0.1f
			);
			PlayerCamera(
				glm::vec3 position, // = glm::vec3(0, 0, 0),
				float horizontalAngle, // = -glm::pi<float>(),
				float verticalAngle, // = 0.f,

				float fov = glm::radians(45.f),
				int width = 800,
				int height = 600,
				float zFar = 1000.f,
				float zNear = 0.1f
			);
			~PlayerCamera();
			PlayerCamera(const PlayerCamera& other);
			PlayerCamera& operator=(const PlayerCamera& other);

			void loopCamera(float delta, bool moveUp, bool moveDown, bool moveLeft, bool moveRight, double xDelta, double yDelta);

		private:
	};

} // namespace CGL

#endif