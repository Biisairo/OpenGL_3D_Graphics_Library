#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Extern/GLMHeader.hpp"

#include "IObject3D.hpp"
#include "Material.hpp"

namespace CGL {

	class Mesh : public IObject3D {
		private:
			bool needToUpdate;

			std::vector<glm::vec3> position;
			std::vector<glm::vec3> normal;
			std::vector<glm::vec2> texCoords;
			std::vector<glm::vec3> tangent;
			std::vector<glm::vec3> bitangent;
			std::vector<glm::vec4> colors;
			std::vector<unsigned int> index;

			Material material;

		public:
			Mesh();
			~Mesh();
			Mesh(const Mesh& other);
			Mesh& operator=(const Mesh& other);

			// update member var
			void setPosition (std::vector<glm::vec3>& position);
			void setNormal (std::vector<glm::vec3>& normal);
			void setTexCoords (std::vector<glm::vec2>& texCoords);
			void setTangent (std::vector<glm::vec3>& tangent);
			void setBitangent (std::vector<glm::vec3>& bitangent);
			void setColors (std::vector<glm::vec4>& colors);
			void setColors (glm::vec4& color);
			void setIndex (std::vector<unsigned int>& index);
			void setMaterial (Material& material);

			ObjectType getObjectType() override;

		private:
			void setVertexData();
			void makeNormal();
			void makeTangentSpace();
	};

} // namespace CGL

#endif