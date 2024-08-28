#include "Device.hpp"

Device::Device() {}

Device::~Device() {}

void Device::init(std::string const &title) {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		std::cerr << "Fail to init glfw" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// // window 생성 및 callback, user point 저장
	// {
	// 	GLFWwindow *window = glfwCreateWindow(this->width, this->height, title.c_str(), NULL, NULL);
	// 	if (!window) {
	// 		glfwTerminate();
	// 		std::cerr << "Fail to make window" << std::endl;
	// 		return;
	// 	}

	// 	glfwSetWindowUserPointer(window, this);
	// 	glfwSetKeyCallback(window, keyCallback);
	// 	glfwSetMouseButtonCallback(window, mouseCallback);
	// 	glfwSetScrollCallback(window, scrollCallback); 

	// 	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
	// 	glfwMakeContextCurrent(window);
	// }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
		return;
    }
}

void Device::setting() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

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

void Device::updateCamera(int ID) {
	
}

void Device::deleteCamera(int ID) {
	
}

void Device::enqueueUserInput(UserInput userInput) {
	this->userInput.push(userInput);
}









// callback function
// 키보드 입력 콜백
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;

	UserInput userInput;
	userInput.userInputType = NONE;

	switch (key) {
		case GLFW_KEY_SPACE:
			userInput.userInputType = KEY_SPACE;
			break;
		case GLFW_KEY_APOSTROPHE:
			userInput.userInputType = KEY_APOSTROPHE;
			break;
		case GLFW_KEY_COMMA:
			userInput.userInputType = KEY_COMMA;
			break;
		case GLFW_KEY_MINUS:
			userInput.userInputType = KEY_MINUS;
			break;
		case GLFW_KEY_PERIOD:
			userInput.userInputType = KEY_PERIOD;
			break;
		case GLFW_KEY_SLASH:
			userInput.userInputType = KEY_SLASH;
			break;
		case GLFW_KEY_0:
			userInput.userInputType = KEY_0;
			break;
		case GLFW_KEY_1:
			userInput.userInputType = KEY_1;
			break;
		case GLFW_KEY_2:
			userInput.userInputType = KEY_2;
			break;
		case GLFW_KEY_3:
			userInput.userInputType = KEY_3;
			break;
		case GLFW_KEY_4:
			userInput.userInputType = KEY_4;
			break;
		case GLFW_KEY_5:
			userInput.userInputType = KEY_5;
			break;
		case GLFW_KEY_6:
			userInput.userInputType = KEY_6;
			break;
		case GLFW_KEY_7:
			userInput.userInputType = KEY_7;
			break;
		case GLFW_KEY_8:
			userInput.userInputType = KEY_8;
			break;
		case GLFW_KEY_9:
			userInput.userInputType = KEY_9;
			break;
		case GLFW_KEY_SEMICOLON:
			userInput.userInputType = KEY_SEMICOLON;
			break;
		case GLFW_KEY_EQUAL:
			userInput.userInputType = KEY_EQUAL;
			break;
		case GLFW_KEY_A:
			userInput.userInputType = KEY_A;
			break;
		case GLFW_KEY_B:
			userInput.userInputType = KEY_B;
			break;
		case GLFW_KEY_C:
			userInput.userInputType = KEY_C;
			break;
		case GLFW_KEY_D:
			userInput.userInputType = KEY_D;
			break;
		case GLFW_KEY_E:
			userInput.userInputType = KEY_E;
			break;
		case GLFW_KEY_F:
			userInput.userInputType = KEY_F;
			break;
		case GLFW_KEY_G:
			userInput.userInputType = KEY_G;
			break;
		case GLFW_KEY_H:
			userInput.userInputType = KEY_H;
			break;
		case GLFW_KEY_I:
			userInput.userInputType = KEY_I;
			break;
		case GLFW_KEY_J:
			userInput.userInputType = KEY_J;
			break;
		case GLFW_KEY_K:
			userInput.userInputType = KEY_K;
			break;
		case GLFW_KEY_L:
			userInput.userInputType = KEY_L;
			break;
		case GLFW_KEY_M:
			userInput.userInputType = KEY_M;
			break;
		case GLFW_KEY_N:
			userInput.userInputType = KEY_N;
			break;
		case GLFW_KEY_O:
			userInput.userInputType = KEY_O;
			break;
		case GLFW_KEY_P:
			userInput.userInputType = KEY_P;
			break;
		case GLFW_KEY_Q:
			userInput.userInputType = KEY_Q;
			break;
		case GLFW_KEY_R:
			userInput.userInputType = KEY_R;
			break;
		case GLFW_KEY_S:
			userInput.userInputType = KEY_S;
			break;
		case GLFW_KEY_T:
			userInput.userInputType = KEY_T;
			break;
		case GLFW_KEY_U:
			userInput.userInputType = KEY_U;
			break;
		case GLFW_KEY_V:
			userInput.userInputType = KEY_V;
			break;
		case GLFW_KEY_W:
			userInput.userInputType = KEY_W;
			break;
		case GLFW_KEY_X:
			userInput.userInputType = KEY_X;
			break;
		case GLFW_KEY_Y:
			userInput.userInputType = KEY_Y;
			break;
		case GLFW_KEY_Z:
			userInput.userInputType = KEY_Z;
			break;
		case GLFW_KEY_LEFT_BRACKET:
			userInput.userInputType = KEY_LEFT_BRACKET;
			break;
		case GLFW_KEY_BACKSLASH:
			userInput.userInputType = KEY_BACKSLASH;
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			userInput.userInputType = KEY_RIGHT_BRACKET;
			break;
		case GLFW_KEY_GRAVE_ACCENT:
			userInput.userInputType = KEY_GRAVE_ACCENT;
			break;
		case GLFW_KEY_WORLD_1:
			userInput.userInputType = KEY_WORLD_1;
			break;
		case GLFW_KEY_WORLD_2:
			userInput.userInputType = KEY_WORLD_2;
			break;
		case GLFW_KEY_ESCAPE:
			userInput.userInputType = KEY_ESCAPE;
			break;
		case GLFW_KEY_ENTER:
			userInput.userInputType = KEY_ENTER;
			break;
		case GLFW_KEY_TAB:
			userInput.userInputType = KEY_TAB;
			break;
		case GLFW_KEY_BACKSPACE:
			userInput.userInputType = KEY_BACKSPACE;
			break;
		case GLFW_KEY_INSERT:
			userInput.userInputType = KEY_INSERT;
			break;
		case GLFW_KEY_DELETE:
			userInput.userInputType = KEY_DELETE;
			break;
		case GLFW_KEY_RIGHT:
			userInput.userInputType = KEY_RIGHT;
			break;
		case GLFW_KEY_LEFT:
			userInput.userInputType = KEY_LEFT;
			break;
		case GLFW_KEY_DOWN:
			userInput.userInputType = KEY_DOWN;
			break;
		case GLFW_KEY_UP:
			userInput.userInputType = KEY_UP;
			break;
		case GLFW_KEY_PAGE_UP:
			userInput.userInputType = KEY_PAGE_UP;
			break;
		case GLFW_KEY_PAGE_DOWN:
			userInput.userInputType = KEY_PAGE_DOWN;
			break;
		case GLFW_KEY_HOME:
			userInput.userInputType = KEY_HOME;
			break;
		case GLFW_KEY_END:
			userInput.userInputType = KEY_END;
			break;
		case GLFW_KEY_CAPS_LOCK:
			userInput.userInputType = KEY_CAPS_LOCK;
			break;
		case GLFW_KEY_SCROLL_LOCK:
			userInput.userInputType = KEY_SCROLL_LOCK;
			break;
		case GLFW_KEY_NUM_LOCK:
			userInput.userInputType = KEY_NUM_LOCK;
			break;
		case GLFW_KEY_PRINT_SCREEN:
			userInput.userInputType = KEY_PRINT_SCREEN;
			break;
		case GLFW_KEY_PAUSE:
			userInput.userInputType = KEY_PAUSE;
			break;
		case GLFW_KEY_F1:
			userInput.userInputType = KEY_F1;
			break;
		case GLFW_KEY_F2:
			userInput.userInputType = KEY_F2;
			break;
		case GLFW_KEY_F3:
			userInput.userInputType = KEY_F3;
			break;
		case GLFW_KEY_F4:
			userInput.userInputType = KEY_F4;
			break;
		case GLFW_KEY_F5:
			userInput.userInputType = KEY_F5;
			break;
		case GLFW_KEY_F6:
			userInput.userInputType = KEY_F6;
			break;
		case GLFW_KEY_F7:
			userInput.userInputType = KEY_F7;
			break;
		case GLFW_KEY_F8:
			userInput.userInputType = KEY_F8;
			break;
		case GLFW_KEY_F9:
			userInput.userInputType = KEY_F9;
			break;
		case GLFW_KEY_F10:
			userInput.userInputType = KEY_F10;
			break;
		case GLFW_KEY_F11:
			userInput.userInputType = KEY_F11;
			break;
		case GLFW_KEY_F12:
			userInput.userInputType = KEY_F12;
			break;
		case GLFW_KEY_F13:
			userInput.userInputType = KEY_F13;
			break;
		case GLFW_KEY_F14:
			userInput.userInputType = KEY_F14;
			break;
		case GLFW_KEY_F15:
			userInput.userInputType = KEY_F15;
			break;
		case GLFW_KEY_F16:
			userInput.userInputType = KEY_F16;
			break;
		case GLFW_KEY_F17:
			userInput.userInputType = KEY_F17;
			break;
		case GLFW_KEY_F18:
			userInput.userInputType = KEY_F18;
			break;
		case GLFW_KEY_F19:
			userInput.userInputType = KEY_F19;
			break;
		case GLFW_KEY_F20:
			userInput.userInputType = KEY_F20;
			break;
		case GLFW_KEY_F21:
			userInput.userInputType = KEY_F21;
			break;
		case GLFW_KEY_F22:
			userInput.userInputType = KEY_F22;
			break;
		case GLFW_KEY_F23:
			userInput.userInputType = KEY_F23;
			break;
		case GLFW_KEY_F24:
			userInput.userInputType = KEY_F24;
			break;
		case GLFW_KEY_F25:
			userInput.userInputType = KEY_F25;
			break;
		case GLFW_KEY_KP_0:
			userInput.userInputType = KEY_KP_0;
			break;
		case GLFW_KEY_KP_1:
			userInput.userInputType = KEY_KP_1;
			break;
		case GLFW_KEY_KP_2:
			userInput.userInputType = KEY_KP_2;
			break;
		case GLFW_KEY_KP_3:
			userInput.userInputType = KEY_KP_3;
			break;
		case GLFW_KEY_KP_4:
			userInput.userInputType = KEY_KP_4;
			break;
		case GLFW_KEY_KP_5:
			userInput.userInputType = KEY_KP_5;
			break;
		case GLFW_KEY_KP_6:
			userInput.userInputType = KEY_KP_6;
			break;
		case GLFW_KEY_KP_7:
			userInput.userInputType = KEY_KP_7;
			break;
		case GLFW_KEY_KP_8:
			userInput.userInputType = KEY_KP_8;
			break;
		case GLFW_KEY_KP_9:
			userInput.userInputType = KEY_KP_9;
			break;
		case GLFW_KEY_KP_DECIMAL:
			userInput.userInputType = KEY_KP_DECIMAL;
			break;
		case GLFW_KEY_KP_DIVIDE:
			userInput.userInputType = KEY_KP_DIVIDE;
			break;
		case GLFW_KEY_KP_MULTIPLY:
			userInput.userInputType = KEY_KP_MULTIPLY;
			break;
		case GLFW_KEY_KP_SUBTRACT:
			userInput.userInputType = KEY_KP_SUBTRACT;
			break;
		case GLFW_KEY_KP_ADD:
			userInput.userInputType = KEY_KP_ADD;
			break;
		case GLFW_KEY_KP_ENTER:
			userInput.userInputType = KEY_KP_ENTER;
			break;
		case GLFW_KEY_KP_EQUAL:
			userInput.userInputType = KEY_KP_EQUAL;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			userInput.userInputType = KEY_LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			userInput.userInputType = KEY_LEFT_CONTROL;
			break;
		case GLFW_KEY_LEFT_ALT:
			userInput.userInputType = KEY_LEFT_ALT;
			break;
		case GLFW_KEY_LEFT_SUPER:
			userInput.userInputType = KEY_LEFT_SUPER;
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			userInput.userInputType = KEY_RIGHT_SHIFT;
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			userInput.userInputType = KEY_RIGHT_CONTROL;
			break;
		case GLFW_KEY_RIGHT_ALT:
			userInput.userInputType = KEY_RIGHT_ALT;
			break;
		case GLFW_KEY_RIGHT_SUPER:
			userInput.userInputType = KEY_RIGHT_SUPER;
			break;
		case GLFW_KEY_MENU:
			userInput.userInputType = KEY_MENU;
			break;
	}

	switch (action)
	{
	case GLFW_PRESS:
		userInput.press = true;
		break;
	case GLFW_RELEASE:
		userInput.press = false;
		break;
	}

	device->enqueueUserInput(userInput);
}

// 마우스 버튼 콜백
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 커서 위치 콜백
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 커서 진입/이탈 콜백
static void cursor_enter_callback(GLFWwindow* window, int entered) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 스크롤 콜백
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 프레임버퍼 크기 콜백
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 윈도우 포커스 콜백
static void window_focus_callback(GLFWwindow* window, int focused) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 윈도우 위치 콜백
static void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 윈도우 크기 콜백
static void window_size_callback(GLFWwindow* window, int width, int height) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 윈도우 닫기 콜백
static void window_close_callback(GLFWwindow* window) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// 윈도우 최대화/최소화 콜백
static void window_maximize_callback(GLFWwindow* window, int maximized) {
	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
	if (!device)
		return;
}

// // 모니터 콜백
// static void monitor_callback(GLFWmonitor* monitor, int event) {
// 	Device *device = static_cast<Device*>(glfwGetWindowUserPointer(window));
// 	if (!device)
// 		return;
// }

// error message
static void error_callback(int error, const char *des) {
	std::cout << des << std::endl;
}