#ifndef USER_INPUT_HPP
#define USER_INPUT_HPP

#include <iostream>

#include "Extern/OpenGLHeader.hpp"

#include "Device.hpp"

namespace CGL {

	typedef struct UserInput {
		UserInputType userInputType;
		bool press;

		double x, y;

		UserInput() {
			userInputType = NONE;
			press = false;
			x = 0.f;
			y = 0.f;
		}
	};

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

	enum UserInputType {
		NONE,

		// keyboard printable key
		KEY_SPACE,
		KEY_APOSTROPHE,
		KEY_COMMA,
		KEY_MINUS,
		KEY_PERIOD,
		KEY_SLASH,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_SEMICOLON,
		KEY_EQUAL,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_LEFT_BRACKET,
		KEY_BACKSLASH,
		KEY_RIGHT_BRACKET,
		KEY_GRAVE_ACCENT,
		KEY_WORLD_1,
		KEY_WORLD_2,

		// keyboard function keys
		KEY_ESCAPE,
		KEY_ENTER,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_INSERT,
		KEY_DELETE,
		KEY_RIGHT,
		KEY_LEFT,
		KEY_DOWN,
		KEY_UP,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_HOME,
		KEY_END,
		KEY_CAPS_LOCK,
		KEY_SCROLL_LOCK,
		KEY_NUM_LOCK,
		KEY_PRINT_SCREEN,
		KEY_PAUSE,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_F13,
		KEY_F14,
		KEY_F15,
		KEY_F16,
		KEY_F17,
		KEY_F18,
		KEY_F19,
		KEY_F20,
		KEY_F21,
		KEY_F22,
		KEY_F23,
		KEY_F24,
		KEY_F25,
		KEY_KP_0,
		KEY_KP_1,
		KEY_KP_2,
		KEY_KP_3,
		KEY_KP_4,
		KEY_KP_5,
		KEY_KP_6,
		KEY_KP_7,
		KEY_KP_8,
		KEY_KP_9,
		KEY_KP_DECIMAL,
		KEY_KP_DIVIDE,
		KEY_KP_MULTIPLY,
		KEY_KP_SUBTRACT,
		KEY_KP_ADD,
		KEY_KP_ENTER,
		KEY_KP_EQUAL,
		KEY_LEFT_SHIFT,
		KEY_LEFT_CONTROL,
		KEY_LEFT_ALT,
		KEY_LEFT_SUPER,
		KEY_RIGHT_SHIFT,
		KEY_RIGHT_CONTROL,
		KEY_RIGHT_ALT,
		KEY_RIGHT_SUPER,
		KEY_MENU,

		// mouse
		MOUSE_BUTTON_1,
		MOUSE_BUTTON_2,
		MOUSE_BUTTON_3,
		MOUSE_BUTTON_4,
		MOUSE_BUTTON_5,
		MOUSE_BUTTON_6,
		MOUSE_BUTTON_7,
		MOUSE_BUTTON_8,

		// mouse position double xpos, ypos
		MOUSE_POSITION,

		// mouse on window
		MOUSE_ENTER,
		MOUSE_EXIT,

		// mouse scroll double xoffset, yoffset
		MOUSE_SCROLL,

		// framebuffer size int width, height
		FRAME_SIZE,

		// window focus
		WINDOW_FOCUS,
		WINDOW_FOCUSOUT,

		// window position int xpos, ypos
		WINDOW_POSITION,

		// window size int width, height
		WINDOW_SIZE,

		// window close
		WINDOW_CLOSE,

		// window maximize
		WINDOW_MAXIMIZE,

		// monitor connect, disconnect
		MONITOR_CONNECTED,
		MONITOR_DISCONNECTED
	};

} // namespace CGL

#endif