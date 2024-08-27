#include "main.hpp"
#include "Mesh.hpp"

int main(int ac, char** av) {
	std::cout << "hello world!" << std::endl;

	Device device;

	Mesh mesh0(&device);
	{
		Mesh mesh3(&device);
		mesh3.test();
	}
	Mesh mesh1(&device);
	Mesh mesh2(&device);
	mesh0.test();
	mesh1.test();
	mesh2.test();
}