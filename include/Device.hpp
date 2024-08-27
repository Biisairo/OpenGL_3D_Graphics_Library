#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "pch.hpp"

struct MeshObject {
	GLuint VAO;
	std::vector<GLuint> VBOs;
};

class Device {
	private:
		std::map<uint, MeshObject> mesh_objects;

	public:
		Device();
		~Device();

		void updateMesh(
			int ID,
			std::vector<glm::vec3>& vertex,
			std::vector<glm::vec3>& normal,
			std::vector<glm::vec2>& UV
		);

		void deleteMesh(int ID);

		void updateCamera(int ID);

		void deleteCamera(int ID);
};

#endif