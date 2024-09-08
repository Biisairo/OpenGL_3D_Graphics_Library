#include "main.hpp"

#include "Mesh.hpp"
#include "Device.hpp"

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

	mesh.setPosition(point);
	mesh.setIndex(idx);

	while (1)
	{
		glfwPollEvents();
		mesh.drawMesh();
	}
}