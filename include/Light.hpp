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

			glm::vec4 ambientcolor = glm::vec4(1, 1, 1, 1);
			glm::vec4 diffusecolor = glm::vec4(1, 1, 1, 1);
			glm::vec4 specularcolor = glm::vec4(1, 1, 1, 1);

			// 강도
			float intensity = 1.f;

			// 감쇄 상수
			float constantAttenuation = 1;
			float linearAttenuation = 0;
			float quadraticAttenuation = 0;
			// (1 / constant + linear × d + quadratic × d x d), d 는 거리

			// multiple minus when directional light
			glm::vec4 position = glm::vec4(0, 0, 0, 1);

			// only for emitType 2, spotlight
			glm::vec4 emitDirection = glm::vec4(0, 0, 0, 0);
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
			void setAmbientcolor(glm::vec4 ambientcolor);
			void setDiffusecolor(glm::vec4 diffusecolor);
			void setSpecularcolor(glm::vec4 specularcolor);
			void setIntensity(float intensity);
			void setConstantAttenuation(float constantAttenuation);
			void setLinearAttenuation(float linearAttenuation);
			void setQuadraticAttenuation(float quadraticAttenuation);
			void setPosition(glm::vec4 position);
			void setEmitDirection(glm::vec4 emitDirection);
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