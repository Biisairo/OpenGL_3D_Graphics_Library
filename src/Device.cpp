#include "Device.hpp"

// device /////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGL::Device& CGL::Device::getInstance() {
	static CGL::Device instance;
	return instance;
}

void CGL::Device::init() {
	glfwSetErrorCallback(CGL::error_callback);

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

void CGL::Device::createWindow(std::string const &title, int width, int height) {
	this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return;
    }

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	// glDisable(GL_CULL_FACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void CGL::Device::setup() {
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	
	for (int i = 0; i < MAX_LIGHT_COUNT; i++) {
		this->framebufferManager.addLightFramebuffer("shadowMap[" + std::to_string(i) + "]", 1024, 1024);
	}

	this->framebufferManager.addFramebuffer("default", width, height);
	this->framebufferManager.addHDRFramebuffer("defaultHDR", width, height);
	this->defaultRenderFramebufferName = "default";
}

void CGL::Device::loopBeginProcess() {
	glClearColor(0.1, 0.7, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
}

void CGL::Device::loopEndProcess() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}

void CGL::Device::getError() {
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) {
		std::cout << "OpenGL Error" << std::endl;
		switch (err) {
			case GL_INVALID_ENUM:
				std::cout << "GL_INVALID_ENUM" << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cout << "GL_INVALID_VALUE" << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cout << "GL_INVALID_OPERATION" << std::endl;
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cout << "GL_OUT_OF_MEMORY" << std::endl;
				break;
			case GL_STACK_UNDERFLOW:
				std::cout << "GL_STACK_UNDERFLOW" << std::endl;
				break;
			case GL_STACK_OVERFLOW:
				std::cout << "GL_STACK_OVERFLOW" << std::endl;
				break;
		}
		exit(1);
	}
}

void CGL::Device::setMouseMode(MouseType mouseType) {
	GLint GLMouseType = MOUSE_NORMAL;
	switch (mouseType) {
		case MOUSE_NORMAL:
			GLMouseType = GLFW_CURSOR_NORMAL;
			break;
		case MOUSE_HIDDEN:
			GLMouseType = GLFW_CURSOR_HIDDEN;
			break;
		case MOUSE_DISABLED:
			GLMouseType = GLFW_CURSOR_DISABLED;
			break;
		case MOUSE_CAPTURED:
			GLMouseType = GLFW_CURSOR_CAPTURED;
			break;
	}
	glfwSetInputMode(this->window, GLFW_CURSOR, GLMouseType);
}

void CGL::Device::render(CGL::Scene* scene) {
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);

	// ready uniform
	{
		this->addUniformBlock("Matrices");
		this->addUniformBlock("Lights");
		this->addUniformBlock("Material");
	}

	std::vector<CGL::Mesh*> meshes;
	std::vector<CGL::Light*> lights;

	CGL::IObject3D* root = scene->getRoot();
	this->getMeshes(root, meshes);
	this->registerMeshes(meshes);

	this->getLights(root, lights);
	CGL::LightBuffers lightBuffers = this->trimLights(lights);
	this->registerLights(lightBuffers);

	// add uniform
	{
		std::vector<GLuint> programs = this->getAllPrograms();
		this->registerUniformBlock("Matrices", programs);
		this->registerUniformBlock("Lights", programs);
		this->registerUniformBlock("Material", programs);
	}

	// render shadow
	for (int i = 0; i < lightBuffers.lightCount; i++) {
		// this->framebufferManager.useFramebuffer("default");
		// glViewport(0, 0, width, height);
		// glEnable(GL_DEPTH_TEST);
		// glClearColor(0.1, 0.7, 0.8, 1);
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// {
		// 	this->registerLightView(lightBuffers.light[i]);

		// 	this->drawMeshes(meshes);
		// }
		// this->framebufferManager.useDefaultFramebuffer();

		// glViewport(0, 0, width, height);
		// glEnable(GL_DEPTH_TEST);
		// glClearColor(0.1, 0.7, 0.8, 1);
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// this->drawFrameBuffer("default");


		this->framebufferManager.useFramebuffer("shadowMap[" + std::to_string(i) + "]");
		glViewport(0, 0, 1024, 1024);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);	
		{
			this->registerLightView(lightBuffers.light[i]);

			this->drawShadows(meshes);
		}
		this->framebufferManager.useDefaultFramebuffer();

		// glViewport(0, 0, width, height);
		// glEnable(GL_DEPTH_TEST);
		// glClearColor(0.1, 0.7, 0.8, 1);
		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// this->drawShadowBuffer("shadowMap[" + std::to_string(i) + "]", false);

		// return;
	}

	// render mesh
	CGL::ICamera* camera = scene->getMainCamera();
	this->registerCamera(camera);

	this->framebufferManager.useFramebuffer(this->defaultRenderFramebufferName);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.7, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		for (int i = 0; i < lightBuffers.lightCount; i++) {
			GLuint texture = this->framebufferManager.getTexture("shadowMap[" + std::to_string(i) + "]");
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texture);

			std::vector<programHash> programHashes = this->getAllProgramHashes();
			for (int programHash = 0; programHash < programHashes.size(); programHash++) {
				this->setInt(programHash, "shadowMap[" + std::to_string(i) + "]", i);
			}
		}
		this->drawMeshes(meshes);
	}
	this->framebufferManager.useDefaultFramebuffer();


	this->framebufferManager.useDefaultFramebuffer();
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.7, 0.8, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->drawFrameBuffer(this->defaultRenderFramebufferName);
}

// device /////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////

CGL::Device::Device() {
	;
}

CGL::Device::~Device() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void CGL::Device::getMeshes(IObject3D* object, std::vector<CGL::Mesh*>& meshes) {
	if(object->getObjectType() == OBJECT_MESH) {
		CGL::Mesh* mesh = dynamic_cast<CGL::Mesh*>(object);

		meshes.push_back(mesh);
	}

	std::vector<CGL::IObject3D*> children = object->getChildren();
	for (std::vector<CGL::IObject3D*>::iterator itr = children.begin(); itr != children.end(); itr++) {
		getMeshes(*itr, meshes);
	}
}

void CGL::Device::registerMeshes(std::vector<CGL::Mesh*>& meshes) {
	for (std::vector<CGL::Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		CGL::Mesh* mesh = *it;

		if (mesh->needUpdate()) {
			mesh->setVertexData();

			this->updateMesh(
				mesh->getID(),
				mesh->getPosition(),
				mesh->getNormal(),
				mesh->getTexCoords(),
				mesh->getTangent(),
				mesh->getBitangent(),
				mesh->getColors(),
				mesh->getIndex(),
				mesh->getDrawType(),
				mesh->material.getAmbientColor(),
				mesh->material.getDiffuseColor(),
				mesh->material.getSpecularColor(),
				mesh->material.getAlpha(),
				mesh->material.getShininess()
			);

			mesh->updateDone();
		}
	}
}

void CGL::Device::drawMeshes(std::vector<CGL::Mesh*>& meshes) {
	for (std::vector<CGL::Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		this->drawMesh((*it)->getID(), (*it)->getModel());
	}
}

void CGL::Device::getLights(IObject3D* object, std::vector<CGL::Light*>& lights) {
	if(object->getObjectType() == OBJECT_LIGHT) {
		CGL::Light* light = dynamic_cast<CGL::Light*>(object);

		lights.push_back(light);
	}

	std::vector<CGL::IObject3D*> children = object->getChildren();
	for (std::vector<CGL::IObject3D*>::iterator itr = children.begin(); itr != children.end(); itr++) {
		getLights(*itr, lights);
	}
}

CGL::LightBuffers CGL::Device::trimLights(std::vector<CGL::Light*>& lights) {
	CGL::LightBuffers lightBuffers;

	for (std::vector<CGL::Light*>::iterator it = lights.begin(); it != lights.end(); it++) {
		CGL::Light* light = *it;

		glm::mat4 model = light->getModel();

		glm::mat4 parentModel = glm::mat4(1);
		if (light->getParent() != nullptr)
			parentModel = light->getParent()->getModel();

		CGL::LightBuffer lightBuffer;
		lightBuffer.emitType = light->getLightType();
		lightBuffer.ambientStrength = light->getAmbientStrength();
		lightBuffer.diffuseStrength = light->getDiffuseStrength();
		lightBuffer.specularStrength = light->getSpecularStrength();
		lightBuffer.ambientcolor = light->getAmbientcolor();
		lightBuffer.diffusecolor = light->getDiffusecolor();
		lightBuffer.specularcolor = light->getSpecularcolor();
		lightBuffer.intensity = light->getIntensity();
		lightBuffer.constantAttenuation = light->getConstantAttenuation();
		lightBuffer.linearAttenuation = light->getLinearAttenuation();
		lightBuffer.quadraticAttenuation = light->getQuadraticAttenuation();
		lightBuffer.position = light->getPosition();
		lightBuffer.emitDirection = glm::normalize(model * light->getEmitDirection());
		lightBuffer.innerCutoff = light->getInnerCutoff();
		lightBuffer.outerCutoff = light->getOuterCutoff();

		CGL::LightType lightType = light->getLightType();

		float near = 0.1f;
		float far = 100.f;
		if (lightType == CGL::LIGHT_DIRECTIONAL) {
			float frustrumSize = 10.f;
			lightBuffer.projection = glm::ortho(-frustrumSize, frustrumSize, -frustrumSize, frustrumSize, near, far);
			// lightBuffer.position = glm::vec4(glm::vec3(lightBuffer.position) - 100.f * glm::vec3(lightBuffer.emitDirection), 1);
		} else if (lightType == CGL::LIGHT_SPOT) {
			lightBuffer.projection = glm::perspective(glm::radians(90.f), 1.f, near, far);
		} else {
			std::cout << "unknown light" << std::endl;
			exit(1);
		}

		glm::vec3 lightTarget = glm::vec3(lightBuffer.position) + glm::vec3(lightBuffer.emitDirection);
		lightBuffer.view = glm::lookAt(
			// glm::vec3(0, 0, 0) - 10.f * glm::vec3(lightBuffer.emitDirection),
			// glm::vec3(lightBuffer.position) - 10.f * glm::vec3(lightBuffer.emitDirection),
			glm::vec3(lightBuffer.position),
			lightTarget,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		lightBuffers.light.push_back(lightBuffer);
		lightBuffers.lightCount = lightBuffers.light.size();
	}

	return lightBuffers;
}

void CGL::Device::registerLights(CGL::LightBuffers& lightBuffers) {
this->getError();
	this->useUniformBlock("Lights");
this->getError();
	programHash program;
	{
		std::unordered_map<ShaderType, std::string> shader;
		shader.insert(std::make_pair(VERTEX_SHADER, SHADOW_SHADER_VERT));
		shader.insert(std::make_pair(FRAGMENT_SHADER, SHADOW_SHADER_FRAG));
		std::set<std::string> define;
		program = this->getProgram(shader, define);
	}
this->getError();
	GLuint index =this->getBindingIndex("Lights");
this->getError();
	glBufferData(GL_UNIFORM_BUFFER, sizeof(uint) * 4 + sizeof(CGL::LightBuffer) * lightBuffers.lightCount, NULL, GL_STATIC_DRAW);
this->getError();
	glBindBufferRange(GL_UNIFORM_BUFFER, index, this->getUniformBlockBuffer("Lights"), 0, sizeof(uint) * 4 + sizeof(CGL::LightBuffer) * lightBuffers.lightCount);
this->getError();
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(uint), &(lightBuffers.lightCount));
this->getError();
	if (lightBuffers.lightCount != 0)
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(uint) * 4, sizeof(CGL::LightBuffer) * lightBuffers.lightCount, lightBuffers.light.data());
this->getError();
	this->unuseUniformBlock();

	this->getError();
}

void CGL::Device::registerLightView(CGL::LightBuffer& lightBuffer) {
	this->useUniformBlock("Matrices");

	GLuint index =this->getBindingIndex("Matrices");

	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2 + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, index, this->getUniformBlockBuffer("Matrices"), 0, sizeof(glm::mat4) * 2 + sizeof(glm::vec4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(lightBuffer.projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(lightBuffer.view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, sizeof(glm::vec4), glm::value_ptr(lightBuffer.position));

	this->unuseUniformBlock();

	this->getError();
}

void CGL::Device::drawShadows(std::vector<CGL::Mesh*>& meshes) {
	glCullFace(GL_FRONT);
	for (std::vector<CGL::Mesh*>::iterator it = meshes.begin(); it != meshes.end(); it++) {
		this->drawShadow((*it)->getID(), (*it)->getModel());
	}
	glCullFace(GL_BACK);
}

void CGL::Device::registerCamera(CGL::ICamera* camera) {
	if (camera == nullptr)
		return;
		
	glm::mat4 projection = camera->getProjection();
	glm::mat4 view = camera->getView();
	glm::vec4 viewPos = camera->getViewPos();

	this->useUniformBlock("Matrices");

	GLuint index =this->getBindingIndex("Matrices");

	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2 + sizeof(glm::vec4), NULL, GL_STATIC_DRAW);

	glBindBufferRange(GL_UNIFORM_BUFFER, index, this->getUniformBlockBuffer("Matrices"), 0, sizeof(glm::mat4) * 2 + sizeof(glm::vec4));

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, sizeof(glm::vec4), glm::value_ptr(viewPos));

	this->unuseUniformBlock();

	this->getError();
}

void CGL::Device::drawMesh(objectID ID, glm::mat4 model) {
	if (this->meshes.count(ID)) {
		GLenum glDrawType;

		switch (this->meshes[ID].drawType) {
			case DRAW_TRIANGLES:
				glDrawType = GL_TRIANGLES;
				break;
			case DRAW_LINES:
				glDrawType = GL_LINES;
				break;
			case DRAW_POINTS:
				glDrawType = GL_POINTS;
				break;
			default:
				glDrawType = GL_POINTS;
				break;
		}

		this->useUniformBlock("Material");

		GLuint index =this->getBindingIndex("Material");

		glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 3 + sizeof(float) * 4, NULL, GL_STATIC_DRAW);

		glBindBufferRange(GL_UNIFORM_BUFFER, index, this->getUniformBlockBuffer("Material"), 0, sizeof(glm::vec4) * 3 + sizeof(float) * 4);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(meshes[ID].materialBuffer.ambientColor));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(meshes[ID].materialBuffer.diffuseColor));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec4), glm::value_ptr(meshes[ID].materialBuffer.specularColor));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 3, sizeof(float), &(meshes[ID].materialBuffer.alpha));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 3 + sizeof(float), sizeof(float), &(meshes[ID].materialBuffer.shininess));

		this->unuseUniformBlock();

		this->useProgram(this->meshes[ID].program);
		this->setMat4(this->meshes[ID].program, "MODEL", model);
		this->setBool(this->meshes[ID].program, "IS_RENDER_SHADOW", this->isRenderShadow);
		glBindVertexArray(this->meshes[ID].VAO);
		if (this->meshes[ID].EBO == 0)
			glDrawArrays(glDrawType, 0, this->meshes[ID].count);
		else
			glDrawElements(glDrawType, static_cast<unsigned int>(this->meshes[ID].count), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
		this->useProgram(0);
	}

	this->getError();
}

void CGL::Device::drawShadow(objectID ID, glm::mat4 model) {
	if (this->meshes.count(ID)) {
		GLenum glDrawType;

		switch (this->meshes[ID].drawType) {
			case DRAW_TRIANGLES:
				glDrawType = GL_TRIANGLES;
				break;
			case DRAW_LINES:
				glDrawType = GL_LINES;
				break;
			case DRAW_POINTS:
				glDrawType = GL_POINTS;
				break;
			default:
				glDrawType = GL_POINTS;
				break;
		}

		programHash program;
		{
			std::unordered_map<ShaderType, std::string> shader;
			shader.insert(std::make_pair(VERTEX_SHADER, SHADOW_SHADER_VERT));
			shader.insert(std::make_pair(FRAGMENT_SHADER, SHADOW_SHADER_FRAG));
			std::set<std::string> define;
			program = this->getProgram(shader, define);
		}

		this->useProgram(program);
		this->setMat4(program, "MODEL", model);
		glBindVertexArray(this->meshes[ID].VAO);
		if (this->meshes[ID].EBO == 0)
			glDrawArrays(glDrawType, 0, this->meshes[ID].count);
		else
			glDrawElements(glDrawType, static_cast<unsigned int>(this->meshes[ID].count), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
		this->useProgram(0);
	}

	this->getError();
}

void CGL::Device::renderShadow(bool isRenderShadow) {
	this->isRenderShadow = isRenderShadow;
}

void CGL::Device::drawFrameBuffer(std::string frameBufferName) {
	programHash program;
	{
		std::unordered_map<ShaderType, std::string> shader;
		shader.insert(std::make_pair(VERTEX_SHADER, DEFAULT_SHADER_VERT));
		shader.insert(std::make_pair(FRAGMENT_SHADER, DEFAULT_SHADER_FRAG));
		std::set<std::string> define;
		program = this->getProgram(shader, define);
	}
	this->getError();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	this->getError();

	GLuint frameBufferID = this->framebufferManager.getTexture(frameBufferName);

	this->useProgram(program);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, frameBufferID);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
}

void CGL::Device::drawShadowBuffer(std::string frameBufferName, bool isPerspective) {
	programHash program;
	{
		std::unordered_map<ShaderType, std::string> shader;
		shader.insert(std::make_pair(VERTEX_SHADER, SHADOW_TEST_VERT));
		shader.insert(std::make_pair(FRAGMENT_SHADER, SHADOW_TEST_FRAG));
		std::set<std::string> define;
		program = this->getProgram(shader, define);
	}
	this->getError();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	this->getError();

	GLuint frameBufferID = this->framebufferManager.getTexture(frameBufferName);

	this->useProgram(program);
	this->setBool(program, "PERSPECTIVE", isPerspective);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, frameBufferID);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);
}

// mesh ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Device::updateMesh(
	objectID ID,
	std::vector<glm::vec3> position,
	std::vector<glm::vec3> normal,
	std::vector<glm::vec2> texCoords,
	std::vector<glm::vec3> tangent,
	std::vector<glm::vec3> bitangent,
	std::vector<glm::vec4> colors,
	std::vector<uint> index,
	CGL::DrawType drawType,
	glm::vec4 ambientColor,
	glm::vec4 diffuseColor,
	glm::vec4 specularColor,
	float alpha,
	float shininess
) {
	this->deleteMesh(ID);

	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
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

	programHash program = this->getProgram(shader, define);

	MeshBuffer meshBuffer;
	meshBuffer.VAO = VAO;
	meshBuffer.VBO = VBO;
	meshBuffer.EBO = EBO;
	if (EBO == 0)
		meshBuffer.count = position.size();
	else
		meshBuffer.count = index.size();
	meshBuffer.program = program;
	meshBuffer.drawType = drawType;

	meshBuffer.materialBuffer.ambientColor = ambientColor;
	meshBuffer.materialBuffer.diffuseColor = diffuseColor;
	meshBuffer.materialBuffer.specularColor = specularColor;
	meshBuffer.materialBuffer.alpha = alpha;
	meshBuffer.materialBuffer.shininess = shininess;

	this->meshes.insert(std::make_pair(ID, meshBuffer));

	this->getError();
}

void CGL::Device::deleteMesh(objectID ID) {
	if (this->meshes.count(ID)) {
		if (this->meshes[ID].EBO)
			glDeleteBuffers(1, &(this->meshes[ID].EBO));
		glDeleteBuffers(1, &(this->meshes[ID].VBO));
		glDeleteVertexArrays(1, &(this->meshes[ID].VAO));

		this->meshes.erase(ID);
	}
}

// uniform ////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Device::addUniformBlock(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName) == 0) {
		GLuint index = this->getBindingIndex(uniformBlockName);
		UniformBlock ub;

		GLuint uniformBlockBuffer;
		glGenBuffers(1, &uniformBlockBuffer);

		ub.uniformBlockBuffer = uniformBlockBuffer;

		this->uniformBlocks.insert(std::make_pair(uniformBlockName, ub));
	}
}

void CGL::Device::registerUniformBlock(std::string const &uniformBlockName, std::vector<GLuint> &programs) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		GLuint index =this->getBindingIndex(uniformBlockName);

		for (int i = 0; i < programs.size(); i++) {
			if (this->uniformBlocks[uniformBlockName].uniformBlockIndex.count(programs[i]))
				continue;

			GLuint id = glGetUniformBlockIndex(programs[i], uniformBlockName.c_str());
			if (id == GL_INVALID_INDEX)
				continue;

			this->uniformBlocks[uniformBlockName].uniformBlockIndex.insert(std::make_pair(programs[i], id));
			glUniformBlockBinding(programs[i], id, index);

			this->getError();
		}
	} else {
		std::cout << uniformBlockName << " is not added" << std::endl;
	}
}

GLuint CGL::Device::getUniformBlockBuffer(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName))
		return this->uniformBlocks[uniformBlockName].uniformBlockBuffer;
	return 0;
}

void CGL::Device::deleteUniformBlock(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		glDeleteBuffers(1, &this->uniformBlocks[uniformBlockName].uniformBlockBuffer);
	}
}

void CGL::Device::useUniformBlock(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		glBindBuffer(GL_UNIFORM_BUFFER, this->uniformBlocks[uniformBlockName].uniformBlockBuffer);
	}
}

void CGL::Device::unuseUniformBlock() {
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint CGL::Device::getBindingIndex(std::string const &uniformBlockName) {
	static GLuint index = 0;

	if (this->uniformBufferIndexMap.count(uniformBlockName))
		return this->uniformBufferIndexMap[uniformBlockName];

	GLuint res = index;
	index = (index + 1) % GL_MAX_UNIFORM_BUFFER_BINDINGS;

	this->uniformBufferIndexMap.insert(std::make_pair(uniformBlockName, res));
	return res;
}

void CGL::Device::useHDR(bool isUseHDR) {
	if (isUseHDR)
		this->defaultRenderFramebufferName = "defaultHDR";
	else
		this->defaultRenderFramebufferName = "default";
}

// programs ///////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

programHash CGL::Device::getProgram(
	std::unordered_map<CGL::ShaderType, std::string> &shader,
	std::set<std::string> &define
) {
	programHash hashCode = this->getProgramHash(shader, define);
	GLuint programID = this->getProgramID(hashCode);
	if (programID)
		return hashCode;
	
	return this->loadProgram(shader, define);
}

void CGL::Device::useProgram(programHash hashCode) {
	if (this->programs.count(hashCode))
		glUseProgram(this->programs[hashCode]);
	else
		glUseProgram(0);
}

std::vector<GLuint> CGL::Device::getAllPrograms() {
	std::vector<GLuint> res;
	for (std::unordered_map<programHash, GLuint>::iterator it = this->programs.begin(); it != this->programs.end(); it++) {
		res.push_back(it->second);
	}
	return res;
}

std::vector<programHash> CGL::Device::getAllProgramHashes() {
	std::vector<programHash> res;
	for (std::unordered_map<programHash, GLuint>::iterator it = this->programs.begin(); it != this->programs.end(); it++) {
		res.push_back(it->first);
	}
	return res;
}

void CGL::Device::setBool(programHash hashCode, std::string const &name, bool value) {         
	if (this->programs.count(hashCode))
		glUniform1i(glGetUniformLocation(this->programs[hashCode], name.c_str()), (int)value); 
}
void CGL::Device::setInt(programHash hashCode, std::string const &name, int value) { 
	if (this->programs.count(hashCode))
		glUniform1i(glGetUniformLocation(this->programs[hashCode], name.c_str()), value); 
}
void CGL::Device::setFloat(programHash hashCode, std::string const &name, float value) { 
	if (this->programs.count(hashCode))
		glUniform1f(glGetUniformLocation(this->programs[hashCode], name.c_str()), value); 
}
void CGL::Device::setVec2(programHash hashCode, std::string const &name, glm::vec2 value) { 
	if (this->programs.count(hashCode))
		glUniform2fv(glGetUniformLocation(this->programs[hashCode], name.c_str()), 1, &value[0]); 
}
void CGL::Device::setVec2(programHash hashCode, std::string const &name, float x, float y) { 
	if (this->programs.count(hashCode))
		glUniform2f(glGetUniformLocation(this->programs[hashCode], name.c_str()), x, y); 
}
void CGL::Device::setVec3(programHash hashCode, std::string const &name, glm::vec3 value) { 
	if (this->programs.count(hashCode))
		glUniform3fv(glGetUniformLocation(this->programs[hashCode], name.c_str()), 1, &value[0]); 
}
void CGL::Device::setVec3(programHash hashCode, std::string const &name, float x, float y, float z) { 
	if (this->programs.count(hashCode))
		glUniform3f(glGetUniformLocation(this->programs[hashCode], name.c_str()), x, y, z); 
}
void CGL::Device::setVec4(programHash hashCode, std::string const &name, glm::vec4 value) { 
	if (this->programs.count(hashCode))
		glUniform4fv(glGetUniformLocation(this->programs[hashCode], name.c_str()), 1, &value[0]); 
}
void CGL::Device::setVec4(programHash hashCode, std::string const &name, float x, float y, float z, float w)  { 
	if (this->programs.count(hashCode))
		glUniform4f(glGetUniformLocation(this->programs[hashCode], name.c_str()), x, y, z, w); 
}
void CGL::Device::setMat3(programHash hashCode, std::string const &name, glm::mat3 &mat) {
	if (this->programs.count(hashCode))
		glUniformMatrix3fv(glGetUniformLocation(this->programs[hashCode], name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void CGL::Device::setMat4(programHash hashCode, std::string const &name, glm::mat4 &mat) {
	if (this->programs.count(hashCode))
		glUniformMatrix4fv(glGetUniformLocation(this->programs[hashCode], name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

// programs ///////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////

GLuint CGL::Device::loadShader(CGL::ShaderType shaderType, std::string const &fileName, std::set<std::string> &define) {
	std::string shaderCode = "#version 410 core\n";
	shaderCode += "#define MAX_LIGHT_COUNT ";
	shaderCode += std::to_string(MAX_LIGHT_COUNT);
	shaderCode += "\n";
	for (std::set<std::string>::iterator it = define.begin(); it != define.end(); it++) {
		shaderCode += "#define " + *it + "\n";
	}
	shaderCode += loadShaderCode(fileName);

	GLenum type;
	switch (shaderType) {
		case VERTEX_SHADER:
			type = GL_VERTEX_SHADER;
			break;
		case TESS_CONTROL_SHADER:
			type = GL_TESS_CONTROL_SHADER;
			break;
		case TESS_EVALUATION_SHADER:
			type = GL_TESS_EVALUATION_SHADER;
			break;
		case GEOMETRY_SHADER:
			type = GL_GEOMETRY_SHADER;
			break;
		case FRAGMENT_SHADER:
			type = GL_FRAGMENT_SHADER;
			break;
		case COMPUTE_SHADER:
			type = GL_COMPUTE_SHADER;
			break;
	}

	GLuint id = glCreateShader(type);
	const GLchar *source = shaderCode.c_str();
	const GLint length = shaderCode.length();
	glShaderSource(id, 1, &source, &length);

	glCompileShader(id);

	GLint check;
	glGetShaderiv(id, GL_COMPILE_STATUS, &check);
	if (check == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		std::vector<GLchar> infoLog(infoLogLength);
		glGetShaderInfoLog(id, infoLogLength, &infoLogLength, infoLog.data());

		glDeleteShader(id);

		std::cerr << fileName << " not compiled" << std::endl;
		std::cerr << "Shader compile log: " << infoLog.data() << std::endl;
		return 0;
	};

	return id;
}

programHash CGL::Device::loadProgram(
	std::unordered_map<CGL::ShaderType, std::string> &shader,
	std::set<std::string> &define
) {
	GLuint id = glCreateProgram();

	std::vector<GLuint> shaderIDs;
	for (std::unordered_map<CGL::ShaderType, std::string>::iterator it = shader.begin(); it != shader.end(); it++) {
		GLuint shaderID = this->loadShader(it->first, it->second, define);
		glAttachShader(id, shaderID);
		shaderIDs.push_back(shaderID);
	}

	glLinkProgram(id);

	for (int i = 0; i < shaderIDs.size(); i++) {
		glDetachShader(id, shaderIDs[i]);
		glDeleteShader(shaderIDs[i]);
	}

	GLint check;
	glGetProgramiv(id, GL_LINK_STATUS, &check);
	if (check == GL_FALSE) {
		// 링크 실패 시 오류 로그를 가져옵니다.
		GLint infoLogLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		
		if (infoLogLength > 0) {
			std::vector<char> infoLog(infoLogLength);
			glGetProgramInfoLog(id, infoLogLength, NULL, infoLog.data());
			std::cerr << "Program link error: " << std::endl << infoLog.data() << std::endl;
		}

		glDeleteProgram(id);
		return 0;
	}

	programHash hashCode = this->getProgramHash(shader, define);
	this->programs.insert(std::make_pair(hashCode, id));

	return hashCode;
}

programHash CGL::Device::getProgramHash(
	std::unordered_map<CGL::ShaderType, std::string> &shader,
	std::set<std::string> &define
) {
	std::string programHashKey = "";
	for (int i = VERTEX_SHADER; i <= COMPUTE_SHADER; i++) {
		if (i != VERTEX_SHADER)
			programHashKey += "_";
		if (shader.count(static_cast<ShaderType>(i)))
			programHashKey += shader[static_cast<ShaderType>(i)];
		else
			programHashKey += "NONE";
	}

	for (std::set<std::string>::iterator it = define.begin(); it != define.end(); it++) {
		programHashKey += "_" + *it;
	}

	return std::hash<std::string>()(programHashKey);
}

GLuint CGL::Device::getProgramID(programHash hashCode) {
	if (this->programs.count(hashCode))
		return this->programs[hashCode];
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CallBack ///////////////////////////////////////////////////////////////////////////////////////////////////////////

static void CGL::error_callback(int error, const char *des) {
	std::cout << des << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shader loader //////////////////////////////////////////////////////////////////////////////////////////////////////

static std::string CGL::loadShaderCode(std::string const &fileName) {
	std::string filePath = SHADER_PATH + fileName;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderCode;
    std::string line;

    while (std::getline(file, line)) {
        if (line.find("#include ") != std::string::npos) {
            size_t firstQuote = line.find_first_of("<");
            size_t lastQuote = line.find_last_of(">");
            if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote > firstQuote) {
                std::string includeFile = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                std::string includeCode = loadShaderCode(includeFile);
                shaderCode << includeCode << std::endl;
            }
        } else {
            shaderCode << line << std::endl;
        }
    }

    return shaderCode.str();
}