#ifndef LIGHT_HPP
#define LIGHT_HPP

// #include <vector>

#include "Extern/GLMHeader.hpp"

#include "IObject3D.hpp"

namespace CGL {

	enum LightType {
		LIGHT_DIRECTIONAL = 0,
		LIGHT_POINT,
		LIGHT_SPOT,
	};

	class Light : public IObject3D {
		private:
			LightType lightType = LIGHT_POINT;

			float ambientStrength = 1.f;
			float diffuseStrength = 1.f;
			float specularStrength = 1.f;

			glm::vec3 ambientcolor = glm::vec3(1, 1, 1);
			glm::vec3 diffusecolor = glm::vec3(1, 1, 1);
			glm::vec3 specularcolor = glm::vec3(1, 1, 1);

			// 강도
			float intensity = 1.f;

			// 감쇄 상수
			float constantAttenuation = 1;
			float linearAttenuation = 0;
			float quadraticAttenuation = 0;
			// (1 / constant + linear × d + quadratic × d x d), d 는 거리

			// multiple minus when directional light
			glm::vec3 position = glm::vec3(0, 0, 0);

			// only for emitType 2, spotlight
			glm::vec3 emitDirection = glm::vec3(0, 0, 0);
			float innerCutoff = 0;
			float outerCutoff = 0;

		public:
			Light();
			~Light();
			Light(const Light& other);
			Light& operator=(const Light& other);

			void setLightType(LightType lightType);
			void setAmbientStrength(float ambientStrength);
			void setDiffuseStrength(float diffuseStrength);
			void setSpecularStrength(float specularStrength);
			void setAmbientcolor(glm::vec3 ambientcolor);
			void setDiffusecolor(glm::vec3 diffusecolor);
			void setSpecularcolor(glm::vec3 specularcolor);
			void setIntensity(float intensity);
			void setConstantAttenuation(float constantAttenuation);
			void setLinearAttenuation(float linearAttenuation);
			void setQuadraticAttenuation(float quadraticAttenuation);
			void setPosition(glm::vec3 position);
			void setEmitDirection(glm::vec3 emitDirection);
			void setInnerCutoff(float innerCutoff);
			void setOuterCutoff(float outerCutoff);

			LightType getLightType();
			float getAmbientStrength();
			float getDiffuseStrength();
			float getSpecularStrength();
			glm::vec4 getAmbientcolor();
			glm::vec4 getDiffusecolor();
			glm::vec4 getSpecularcolor();
			float getIntensity();
			float getConstantAttenuation();
			float getLinearAttenuation();
			float getQuadraticAttenuation();
			glm::vec4 getPosition();
			glm::vec4 getEmitDirection();
			float getInnerCutoff();
			float getOuterCutoff();

			ObjectType getObjectType() override;

		private:
	};

} // namespace CGL

#endif