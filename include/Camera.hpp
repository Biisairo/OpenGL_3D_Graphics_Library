#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Extern/GLMHeader.hpp"

#include "IObject3D.hpp"

namespace CGL {

	class Camera : public IObject3D {
		private:
			glm::mat4 projection;
			float fov; // radian
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

		public:
			Camera() = delete;
			Camera(
				glm::vec3 position, // = glm::vec3(0, 0, 0),
				glm::vec3 front, // = glm::vec3(0, 0, -1),
				glm::vec3 up, // = glm::vec3(0, 1, 0),

				float fov = glm::radians(45.f),
				int width = 800,
				int height = 600,
				float zFar = 1000.f,
				float zNear = 0.1f
			);
			Camera(
				glm::vec3 position, // = glm::vec3(0, 0, 0),
				float horizontalAngle, // = -glm::pi<float>(),
				float verticalAngle, // = 0.f,

				float fov = glm::radians(45.f),
				int width = 800,
				int height = 600,
				float zFar = 1000.f,
				float zNear = 0.1f
			);
			~Camera();
			Camera(const Camera& other);
			Camera& operator=(const Camera& other);

			void setViewRotate(glm::vec3 front);
			void addViewRotate(glm::vec3 axis, float angle);
			void addViewRotate(float xDelta, float yDelta);
			void setViewPosition(glm::vec3 position);
			void addViewPosition(glm::vec3 move);
			void addViewPosition(float xOffset, float yOffset, float zOffset);

			glm::mat4 getProjection();
			glm::mat4 getView();
			glm::vec4 getViewPos();

			ObjectType getObjectType() override;

		private:
			void update();

			void updateAngleWhenVectorBase();
			void updateVectorWhenAngleBase();

			using IObject3D::setScale;
			using IObject3D::addScale;
			using IObject3D::setRotate;
			using IObject3D::addRotate;
			using IObject3D::setTranslate;
			using IObject3D::addTranslate;
	};

} // namespace CGL

#endif