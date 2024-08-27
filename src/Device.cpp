#include "Device.hpp"

Device::Device() {}

Device::~Device() {}

void Device::updateMesh(
		int ID,
		std::vector<glm::vec3>& vertex,
		std::vector<glm::vec3>& normal,
		std::vector<glm::vec2>& UV
	) {
	// if (this->vertex.size() == 0)
	// 	return;
	// glGenVertexArrays(1, &this->VAO);
	// glGenBuffers(1, &this->VBO);

	// // std::cout << "Object VAO : " << this->VAO << " , " << "VBO : " << this->VBO << std::endl;

	// glBindVertexArray(this->VAO);
	// glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	// glBufferData(GL_ARRAY_BUFFER,
	// 			this->vertex.size() * sizeof(glm::vec3) + this->normal.size() * sizeof(glm::vec3) + this->texture.size() * sizeof(glm::vec2),
	// 			0,
	// 			GL_STATIC_DRAW);

	// glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertex.size() * sizeof(glm::vec3), this->vertex.data());
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	// if (this->normal.size() != 0) {
	// 	glBufferSubData(GL_ARRAY_BUFFER,
	// 					this->vertex.size() * sizeof(glm::vec3),
	// 					this->normal.size() * sizeof(glm::vec3),
	// 					this->normal.data());
	// 	glEnableVertexAttribArray(1);
	// 	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
	// 						sizeof(glm::vec3),
	// 						(void*)(this->vertex.size() * sizeof(glm::vec3)));
	// }

	// if (this->normal.size() == 0 && this->texture.size() != 0) {
	// 	glBufferSubData(GL_ARRAY_BUFFER,
	// 					this->vertex.size() * sizeof(glm::vec3),
	// 					this->texture.size() * sizeof(glm::vec2),
	// 					this->texture.data());
	// 	glEnableVertexAttribArray(1);
	// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
	// 						sizeof(glm::vec2),
	// 						(void*)(this->vertex.size() * sizeof(glm::vec3)));
	// } else if (this->normal.size() != 0 && this->texture.size() != 0) {
	// 	glBufferSubData(GL_ARRAY_BUFFER,
	// 					this->vertex.size() * sizeof(glm::vec3) + this->normal.size() * sizeof(glm::vec3),
	// 					this->texture.size() * sizeof(glm::vec2),
	// 					this->texture.data());
	// 	glEnableVertexAttribArray(2);
	// 	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
	// 						sizeof(glm::vec2),
	// 						(void*)(this->vertex.size() * sizeof(glm::vec3) + this->normal.size() * sizeof(glm::vec3)));
	// }
	// glBindVertexArray(0);

}

void Device::deleteMesh(int ID) {
	// delete action
}