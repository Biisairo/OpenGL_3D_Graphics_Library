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

			// objectID diffuseMapID;
			// objectID specularMapID;
			// objectID normalMapID;
			// objectID heightMapID;

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
			// objectID getDiffuseMap();
			// objectID getSpecularMap();
			// objectID getNormalMap();
			// objectID getHeightMap();

			// setter
			void setAmbient(glm::vec3 ambient);
			void setDiffuse(glm::vec3 diffuse);
			void setSpecular(glm::vec3 specular);
			void setShininess(float shininess);
			// void setDiffuseMap(objectID ID);
			// void setSpecularMap(objectID ID);
			// void setNormalMap(objectID ID);
			// void setHeightMap(objectID ID);
	};

} // namespace CGL

#endif