#ifndef COMMON_STRUCTURE_HPP
#define COMMON_STRUCTURE_HPP

#include "pch.hpp"
#include "UserInput.hpp"

// camera data
struct CameraDTO {
    uint ID;
    glm::mat4 projecton;
    glm::mat4 view;
	glm::vec3 viewpos;
};

// mesh data
struct MeshDTO {
    uint ID;
	std::vector<glm::vec3> position;
	std::vector<glm::vec3> normal;
	std::vector<glm::vec2> texCoords;
	std::vector<glm::vec3> tangent;
	std::vector<glm::vec3> bitangent;
	std::vector<glm::vec4> colors;
	std::vector<uint> index;
};

// window
struct WindowInfo {
	std::string title;
	GLFWwindow* window;
	std::queue<UserInput> userInput;
};

// mesh
struct MeshObject {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	uint count;
	size_t program;
};

#endif