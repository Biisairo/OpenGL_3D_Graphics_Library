#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Extern/GLMHeader.hpp"

namespace CGL {

	class Material {
		private:
			glm::vec3 ambientColor = glm::vec3(1, 1, 1);
			glm::vec3 diffuseColor = glm::vec3(1, 1, 1);
			glm::vec3 specularColor = glm::vec3(1, 1, 1);
			float alpha = 1.0;
			float shininess = 32;

		public:
			Material();
			~Material();
			Material(const Material& other);
			Material& operator=(const Material& other);

			void setAmbientColor(glm::vec3 ambient);
			void setDiffuseColor(glm::vec3 diffuse);
			void setSpecularColor(glm::vec3 specular);
			void setAlpha(float alpha);
			void setShininess(float shininess);
			
			glm::vec4 getAmbientColor();
			glm::vec4 getDiffuseColor();
			glm::vec4 getSpecularColor();
			float getAlpha();
			float getShininess();
			
	};

} // namespace CGL

#endif