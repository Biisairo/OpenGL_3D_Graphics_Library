#include "main.hpp"
#include "Device.hpp"

int main(int ac, char** av) {
	Device device;
	device.init();
	device.addWindow("test", 500, 500);
	std::cout << "test" << std::endl;
	device.activeWindow("test");
	device.addWindow("test2", 500, 500);
	while (1)
	{
		glfwPollEvents();
	}
}