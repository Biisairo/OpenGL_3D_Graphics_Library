#ifndef DEVICE_HPP
#define DEVICE_HPP

#include "pch.hpp"

#include "ProgramManager.hpp"
#include "UniformBlockManager.hpp"
#include "UserInput.hpp"

struct WindowInfo {
	std::string title;
	GLFWwindow* window;
	std::queue<UserInput> userInput;
};

struct MeshObject {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	uint count;
	size_t program;
};

enum DrawType {
	DRAW_TRIANGLES,
	DRAW_LINE,
	DRAW_POINT,
};

class Device {
	private:
		ProgramManager programManager;
		UniformBlockManager uniformBlockManager;

		std::map<std::string, WindowInfo> windows;

		std::map<uint, MeshObject> mesh_objects;

	public:
		Device();
		~Device();

		void init();
		void setting();

		void addWindow(std::string const &title, double width, double height);
		void activeWindow(std::string const &title);

		void updateMesh(
			uint ID,
			std::vector<glm::vec3> position,
			std::vector<glm::vec3> normal,
			std::vector<glm::vec2> texCoords,
			std::vector<glm::vec3> tangent,
			std::vector<glm::vec3> bitangent,
			std::vector<glm::vec4> colors,
			std::vector<uint> index
		);
		// void updateMesh(texture);
		void deleteMesh(uint ID);
		void draw(uint ID, glm::mat4 model, DrawType drawType = DRAW_TRIANGLES);

		void updateCamera(uint ID);

		void deleteCamera(uint ID);
};

// callback function
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
static void cursor_enter_callback(GLFWwindow* window, int entered);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void window_focus_callback(GLFWwindow* window, int focused);
static void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
static void window_size_callback(GLFWwindow* window, int width, int height);
static void window_close_callback(GLFWwindow* window);
static void window_maximize_callback(GLFWwindow* window, int maximized);
static void monitor_callback(GLFWmonitor* monitor, int event);
static void error_callback(int error, const char *des);
/*
void glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun callback);
void glfwSetMouseButtonCallback(GLFWwindow* window, GLFWmousebuttonfun callback);
void glfwSetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback);
void glfwSetCursorEnterCallback(GLFWwindow* window, GLFWcursorenterfun callback);
void glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun callback);
void glfwSetFramebufferSizeCallback(GLFWwindow* window, GLFWframebuffersizefun callback);
void glfwSetWindowFocusCallback(GLFWwindow* window, GLFWwindowfocusfun callback);
void glfwSetWindowPosCallback(GLFWwindow* window, GLFWwindowposfun callback);
void glfwSetWindowSizeCallback(GLFWwindow* window, GLFWwindowsizefun callback);
void glfwSetWindowCloseCallback(GLFWwindow* window, GLFWwindowclosefun callback);
void glfwSetWindowMaximizeCallback(GLFWwindow* window, GLFWwindowmaximizefun callback);
void glfwSetMonitorCallback(GLFWmonitorfun callback);
void glfwSetErrorCallback(GLFWerrorfun callback);
*/
#endif