#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Extern/GLMHeader.hpp"

#include "IObject3D.hpp"
#include "Material.hpp"

using indice = unsigned int;

namespace CGL {

	// enum
	enum DrawType {
		DRAW_POINTS,
		DRAW_LINES,
		DRAW_TRIANGLES
	};

	class Mesh : public IObject3D {
		private:
			bool needToUpdate;

			std::vector<glm::vec3> position;
			std::vector<glm::vec3> normal;
			std::vector<glm::vec2> texCoords;
			std::vector<glm::vec3> tangent;
			std::vector<glm::vec3> bitangent;
			std::vector<glm::vec4> colors;
			std::vector<indice> index;

			DrawType drawType = DRAW_TRIANGLES;

			Material material;

		public:
			Mesh();
			~Mesh();
			Mesh(const Mesh& other);
			Mesh& operator=(const Mesh& other);

			// update member var
			void setPosition(std::vector<glm::vec3>& position);
			void setNormal(std::vector<glm::vec3>& normal);
			void setTexCoords(std::vector<glm::vec2>& texCoords);
			void setTangent(std::vector<glm::vec3>& tangent);
			void setBitangent(std::vector<glm::vec3>& bitangent);
			void setColors(std::vector<glm::vec4>& colors);
			void setColors(glm::vec4 color);
			void setIndex(std::vector<indice>& index);
			void setDrawType(DrawType drawType);
			void setMaterial(Material& material);

			std::vector<glm::vec3> getPosition();
			std::vector<glm::vec3> getNormal();
			std::vector<glm::vec2> getTexCoords();
			std::vector<glm::vec3> getTangent();
			std::vector<glm::vec3> getBitangent();
			std::vector<glm::vec4> getColors();
			std::vector<indice> getIndex();
			DrawType getDrawType();
			CGL::Material getMaterial();

			void setVertexData();

			ObjectType getObjectType() override;

			bool needUpdate();
			void updateDone();

		private:
			void makeNormal();
			void makeTangentSpace();
	};

} // namespace CGL

#endif