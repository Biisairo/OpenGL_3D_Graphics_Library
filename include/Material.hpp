#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Extern/GLMHeader.hpp"

namespace CGL {

	class Material {
		private:
			glm::vec3 ambient;
			glm::vec3 diffuse;
			glm::vec3 specular;
			float shininess;

			// unsigned int diffuseMapID;
			// unsigned int specularMapID;
			// unsigned int normalMapID;
			// unsigned int heightMapID;

		public:
			Material();
			~Material();
			Material(const Material& other);
			Material& operator=(const Material& other);

			// getter
			glm::vec3 getAmbient();
			glm::vec3 getDiffuse();
			glm::vec3 getSpecular();
			float getShininess();
			// unsigned int getDiffuseMap();
			// unsigned int getSpecularMap();
			// unsigned int getNormalMap();
			// unsigned int getHeightMap();

			// setter
			void setAmbient(glm::vec3 ambient);
			void setDiffuse(glm::vec3 diffuse);
			void setSpecular(glm::vec3 specular);
			void setShininess(float shininess);
			// void setDiffuseMap(unsigned int ID);
			// void setSpecularMap(unsigned int ID);
			// void setNormalMap(unsigned int ID);
			// void setHeightMap(unsigned int ID);
	};

} // namespace CGL

#endif