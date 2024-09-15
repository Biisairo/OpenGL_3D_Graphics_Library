#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Extern/GLMHeader.hpp"

#include "IObject3D.hpp"

namespace CGL {

	class Camera : public IObject3D {
		private:
			glm::mat4 projection;
			float FoV;
			int width;
			int height;
			float zFar;
			float zNear;

			glm::mat4 view;
			glm::vec3 position;
			glm::vec3 front;
			glm::vec3 up;
			glm::vec3 right;
			float horizontalAngle;
			float verticalAngle;

			float moveSpeed;
			float mouseSpeed;

		public:
			Camera() = delete;
			Camera(
				glm::vec3 position, // = glm::vec3(0, 0, 0),
				glm::vec3 front, // = glm::vec3(0, 0, -1),
				glm::vec3 up, // = glm::vec3(0, 1, 0),

				float FoV = 45.f,
				int width = 800,
				int height = 600,
				float zFar = 1000.f,
				float zNear = 0.1f,

				float moveSpeed = 10.f,
				float mouseSpeed = 0.002f
			);
			Camera(
				glm::vec3 position, // = glm::vec3(0, 0, 0),
				float horizontalAngle, // = -glm::pi<float>(),
				float verticalAngle, // = 0.f,

				float FoV = 45.f,
				int width = 800,
				int height = 600,
				float zFar = 1000.f,
				float zNear = 0.1f,

				float moveSpeed = 10.f,
				float mouseSpeed = 0.002f
			);
			~Camera();
			Camera(const Camera& other);
			Camera& operator=(const Camera& other);

			void rotateView(float angle, glm::vec3 axis);
			void rotateView(float xDelta, float yDelta);
			void movePosition(glm::vec3 position);
			void movePosition(float xOffset, float yOffset, float zOffset);

			ObjectType getObjectType() override;

		private:
			void update();

			void updateAngleWhenVectorBase();
			void updateVectorWhenAngleBase();
	};

} // namespace CGL

#endif