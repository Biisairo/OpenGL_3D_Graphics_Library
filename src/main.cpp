#include "main.hpp"

#include "Mesh.hpp"
#include "Device.hpp"
#include "Camera.hpp"

int main(int ac, char** av) {
	
	Device device;
	device.init();
	device.addWindow("test", 500, 500);
	device.activeWindow("test");

	Mesh mesh(&device);

	std::vector<glm::vec3> point;
	point.push_back({0, 0, 0});
	point.push_back({1, 0, 0});
	point.push_back({1, 1, 0});
	point.push_back({0, 1, 0});

	std::vector<uint> idx;
	idx.push_back(0);
	idx.push_back(1);
	idx.push_back(2);
	idx.push_back(0);
	idx.push_back(2);
	idx.push_back(3);

	glm::vec4 color = glm::vec4(0, 0.8, 0.5, 1);

	mesh.setPosition(point);
	mesh.setIndex(idx);
	mesh.setColors(color);

	Camera camera(&device, 500, 500, PROJECTION_PERSPECTIVE, CENTER_CAMERA);

	while (1)
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.1, 0.2, 0.1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

		glfwPollEvents();
		mesh.drawMesh();
	}
}