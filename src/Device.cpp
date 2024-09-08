#include "Device.hpp"

Device::Device() {}

Device::~Device() {}

void Device::init() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		std::cerr << "Fail to init glfw" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
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

void Device::addWindow(std::string const &title, double width, double height) {
	GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::cerr << "Fail to make window" << std::endl;
		return;
	}

	WindowInfo windowInfo;
	windowInfo.title = title;
	windowInfo.window = window;
	this->windows.insert(std::make_pair(title, windowInfo));

	glfwSetWindowUserPointer(window, &this->windows[title]);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowPosCallback(window, window_pos_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetWindowCloseCallback(window, window_close_callback);
	glfwSetWindowMaximizeCallback(window, window_maximize_callback);

	// glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwMakeContextCurrent(window);

	static bool isLoadGlad = false;

	if (isLoadGlad == false)
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize OpenGL context" << std::endl;
			return;
		}

		isLoadGlad = true;
	}

	this->setting();

	glfwMakeContextCurrent(NULL);
}

void Device::activeWindow(std::string const &title) {
	if (this->windows.count(title))
		glfwMakeContextCurrent(this->windows[title].window);
	else if (title.size() == 0)
		glfwMakeContextCurrent(NULL);
}

void Device::updateMesh(
		uint ID,
		std::vector<glm::vec3> position,
		std::vector<glm::vec3> normal,
		std::vector<glm::vec2> texCoords,
		std::vector<glm::vec3> tangent,
		std::vector<glm::vec3> bitangent,
		std::vector<glm::vec4> colors,
		std::vector<GLuint> index
	) {
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLsizeiptr bufferSize = 0;
	bufferSize += position.size() * sizeof(glm::vec3);
	bufferSize += normal.size() * sizeof(glm::vec3);
	bufferSize += texCoords.size() * sizeof(glm::vec2);
	bufferSize += tangent.size() * sizeof(glm::vec3);
	bufferSize += bitangent.size() * sizeof(glm::vec3);
	bufferSize += colors.size() * sizeof(glm::vec4);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, NULL, GL_STATIC_DRAW);  


	GLintptr offsetSize = 0;
	{
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, position.size() * sizeof(glm::vec3), position.data());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offsetSize);
		
		offsetSize += position.size() * sizeof(glm::vec3);
	}

	if (normal.size())
	{
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, normal.size() * sizeof(glm::vec3), normal.data());
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offsetSize);
		
		offsetSize += normal.size() * sizeof(glm::vec3);
	}

	if (texCoords.size())
	{
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, texCoords.size() * sizeof(glm::vec2), texCoords.data());
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)offsetSize);

		offsetSize += texCoords.size() * sizeof(glm::vec2);
	}

	if (tangent.size())
	{
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, tangent.size() * sizeof(glm::vec3), tangent.data());
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offsetSize);

		offsetSize += tangent.size() * sizeof(glm::vec3);
	}

	if (bitangent.size())
	{
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, bitangent.size() * sizeof(glm::vec3), bitangent.data());
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)offsetSize);

		offsetSize += bitangent.size() * sizeof(glm::vec3);
	}

	if (colors.size())
	{
		glBufferSubData(GL_ARRAY_BUFFER, offsetSize, colors.size() * sizeof(glm::vec4), colors.data());
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)offsetSize);

		offsetSize += colors.size() * sizeof(glm::vec4);
	}

	if (index.size()) {
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint), index.data(), GL_STATIC_DRAW);
	} else {
		EBO = 0;
	}

	glBindVertexArray(0);

	std::unordered_map<ShaderType, std::string> shader;
	shader.insert(std::make_pair(VERTEX_SHADER, COMMON_SHADER_VERT));
	shader.insert(std::make_pair(FRAGMENT_SHADER, COMMON_SHADER_FRAG));

	std::set<std::string> define;
	if (normal.size())
		define.insert("USE_NORMAL");
	if (texCoords.size())
		define.insert("USE_TEXCOORD");


	size_t program = this->programManager.getProgram(shader, define);

	MeshObject meshObject;
	meshObject.VAO = VAO;
	meshObject.VBO = VBO;
	meshObject.EBO = EBO;
	if (EBO == 0)
		meshObject.count = position.size();
	else
		meshObject.count = index.size();
	meshObject.program = program;

	this->mesh_objects.insert(std::make_pair(ID, meshObject));
}

void Device::deleteMesh(uint ID) {
	if (this->mesh_objects.count(ID)) {
		glDeleteBuffers(1, &(this->mesh_objects[ID].EBO));
		glDeleteBuffers(1, &(this->mesh_objects[ID].VBO));
		glDeleteVertexArrays(1, &(this->mesh_objects[ID].VAO));

		this->mesh_objects.erase(ID);
	}
}

void Device::draw(uint ID, glm::mat4 model, DrawType drawType) {
	GLenum glDrawType;
	switch (drawType) {
		case DRAW_TRIANGLES:
			glDrawType = GL_TRIANGLES;
			break;
		case DRAW_LINE:
			glDrawType = GL_LINE;
			break;
		case DRAW_POINT:
			glDrawType = GL_POINT;
			break;
		default:
			glDrawType = GL_POINT;
			break;
	}

	if (this->mesh_objects.count(ID)) {
		this->programManager.useProgram(this->mesh_objects[ID].program);
		this->programManager.setMat4(this->mesh_objects[ID].program, "MODEL", model);
		glBindVertexArray(this->mesh_objects[ID].VAO);
		if (this->mesh_objects[ID].EBO == 0)
			glDrawArrays(glDrawType, 0, this->mesh_objects[ID].count);
		else
			glDrawElements(glDrawType, static_cast<unsigned int>(this->mesh_objects[ID].count), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
		this->programManager.useProgram(0);
	}
}

void Device::updateCamera(uint ID) {
	
}

void Device::deleteCamera(uint ID) {
	
}









// callback function
// 키보드 입력 콜백
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
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

	switch (action) {
		case GLFW_PRESS:
			userInput.press = true;
			break;
		case GLFW_RELEASE:
			userInput.press = false;
			break;
	}

	windowInfo->userInput.push(userInput);
}

// 마우스 버튼 콜백
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = NONE;

	switch (button) {
		case GLFW_MOUSE_BUTTON_1:
			userInput.userInputType = MOUSE_BUTTON_1;
			break;
		case GLFW_MOUSE_BUTTON_2:
			userInput.userInputType = MOUSE_BUTTON_2;
			break;
		case GLFW_MOUSE_BUTTON_3:
			userInput.userInputType = MOUSE_BUTTON_3;
			break;
		case GLFW_MOUSE_BUTTON_4:
			userInput.userInputType = MOUSE_BUTTON_4;
			break;
		case GLFW_MOUSE_BUTTON_5:
			userInput.userInputType = MOUSE_BUTTON_5;
			break;
		case GLFW_MOUSE_BUTTON_6:
			userInput.userInputType = MOUSE_BUTTON_6;
			break;
		case GLFW_MOUSE_BUTTON_7:
			userInput.userInputType = MOUSE_BUTTON_7;
			break;
		case GLFW_MOUSE_BUTTON_8:
			userInput.userInputType = MOUSE_BUTTON_8;
			break;
	}

	switch (action) {
		case GLFW_PRESS:
			userInput.press = true;
			break;
		case GLFW_RELEASE:
			userInput.press = false;
			break;
	}

	windowInfo->userInput.push(userInput);
}

// 커서 위치 콜백
static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = MOUSE_POSITION;
	userInput.x = xpos;
	userInput.y = ypos;

	windowInfo->userInput.push(userInput);
}

// 커서 진입/이탈 콜백
static void cursor_enter_callback(GLFWwindow* window, int entered) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = NONE;

	switch (entered) {
		case GLFW_TRUE:
			userInput.userInputType = MOUSE_ENTER;
			break;
		case GLFW_FALSE:
			userInput.userInputType = MOUSE_EXIT;
			break;
	}
	
	windowInfo->userInput.push(userInput);
}

// 스크롤 콜백
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = MOUSE_SCROLL;
	userInput.x = xoffset;
	userInput.y = yoffset;

	windowInfo->userInput.push(userInput);
}

// 프레임버퍼 크기 콜백
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = FRAME_SIZE;
	userInput.x = width;
	userInput.y = height;

	windowInfo->userInput.push(userInput);
}

// 윈도우 포커스 콜백
static void window_focus_callback(GLFWwindow* window, int focused) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = NONE;

	switch (focused) {
		case GLFW_TRUE:
			userInput.userInputType = WINDOW_FOCUS;
			break;
		case GLFW_FALSE:
			userInput.userInputType = WINDOW_FOCUSOUT;
			break;
	}

	windowInfo->userInput.push(userInput);
}

// 윈도우 위치 콜백
static void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = WINDOW_POSITION;
	userInput.x = xpos;
	userInput.y = ypos;

	windowInfo->userInput.push(userInput);
}

// 윈도우 크기 콜백
static void window_size_callback(GLFWwindow* window, int width, int height) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = WINDOW_SIZE;
	userInput.x = width;
	userInput.y = height;

	windowInfo->userInput.push(userInput);
}

// 윈도우 닫기 콜백
static void window_close_callback(GLFWwindow* window) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = WINDOW_CLOSE;

	windowInfo->userInput.push(userInput);
}

// 윈도우 최대화/최소화 콜백
static void window_maximize_callback(GLFWwindow* window, int maximized) {
	WindowInfo* windowInfo = static_cast<WindowInfo*>(glfwGetWindowUserPointer(window));
	if (!windowInfo)
		return;

	UserInput userInput;
	userInput.userInputType = WINDOW_MAXIMIZE;

	windowInfo->userInput.push(userInput);
}

// // 모니터 콜백
// static void monitor_callback(GLFWmonitor* monitor, int event) {
// 	std::queue<UserInput> *userInput = static_cast<std::queue<UserInput>*>(glfwGetWindowUserPointer(window));
// 	if (!/inputQueue/ 	std::queue<UserInput> *userInput = static_cast<std::queue<UserInput>*>(glfwGetWindowUserPointer(window));)
// 		queue;
// }

// error message
static void error_callback(int error, const char *des) {
	std::cout << des << std::endl;
}