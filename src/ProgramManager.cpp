#include "ProgramManager.hpp"

// public
ProgramManager::ProgramManager() {
}

ProgramManager::~ProgramManager() {
	for (std::unordered_map<size_t, GLuint>::iterator it = this->program.begin(); it != this->program.end(); it++) {
		glDeleteProgram(it->second);
	}
}

GLuint ProgramManager::getProgram(
	std::unordered_map<ShaderType, std::string> &shader,
	std::set<std::string> &define
) {
	size_t hashCode = this->getHash(shader, define);
	GLuint programID = this->getID(hashCode);
	if (programID)
		return programID;
	
	return this->loadProgram(shader, define);
}

void ProgramManager::useProgram(size_t hashCode) {
	if (this->program.count(hashCode))
		glUseProgram(this->program[hashCode]);
	else
		glUseProgram(0);
}

std::vector<GLuint> ProgramManager::getAllPrograms() {
	std::vector<GLuint> res;
	for (std::unordered_map<size_t, GLuint>::iterator it = this->program.begin(); it != this->program.end(); it++) {
		res.push_back(it->second);
	}
	return res;
}

// private
GLuint ProgramManager::loadShader(ShaderType shaderType, std::string const &fileName, std::set<std::string> &define) {
	std::string shaderCode = "#version 410 core\n";
	for (std::set<std::string>::iterator it = define.begin(); it != define.end(); it++) {
		shaderCode += "#define " + *it + "\n";
	}
	shaderCode += loadShaderCode(fileName);

	GLenum type;
	switch (shaderType)
	{
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

size_t ProgramManager::loadProgram(
	std::unordered_map<ShaderType, std::string> &shader,
	std::set<std::string> &define
) {
	GLuint id = glCreateProgram();

	std::vector<GLuint> shaderID;
	for (std::unordered_map<ShaderType, std::string>::iterator it = shader.begin(); it != shader.end(); it++) {
		GLuint shader = this->loadShader(it->first, it->second, define);
			glAttachShader(id, shader);
	}

	glLinkProgram(id);

	for (int i = 0; i < shaderID.size(); i++) {
		glDetachShader(id, shaderID[i]);
		glDeleteShader(shaderID[i]);
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

	size_t hashCode = getHash(shader, define);
	this->program[hashCode] = id;

	return hashCode;
}

size_t ProgramManager::getHash(
	std::unordered_map<ShaderType, std::string> &shader,
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

GLuint ProgramManager::getID(size_t hashCode) {
	if (this->program.count(hashCode))
		return this->program[hashCode];
	return 0;
}

// uniform function
void ProgramManager::setBool(size_t hashCode, std::string const &name, bool value) {         
	if (this->program.count(hashCode))
	glUniform1i(glGetUniformLocation(this->program[hashCode], name.c_str()), (int)value); 
}
void ProgramManager::setInt(size_t hashCode, std::string const &name, int value) { 
	if (this->program.count(hashCode))
	glUniform1i(glGetUniformLocation(this->program[hashCode], name.c_str()), value); 
}
void ProgramManager::setFloat(size_t hashCode, std::string const &name, float value) { 
	if (this->program.count(hashCode))
	glUniform1f(glGetUniformLocation(this->program[hashCode], name.c_str()), value); 
}
void ProgramManager::setVec2(size_t hashCode, std::string const &name, glm::vec2 value) { 
	if (this->program.count(hashCode))
	glUniform2fv(glGetUniformLocation(this->program[hashCode], name.c_str()), 1, &value[0]); 
}
void ProgramManager::setVec2(size_t hashCode, std::string const &name, float x, float y) { 
	if (this->program.count(hashCode))
	glUniform2f(glGetUniformLocation(this->program[hashCode], name.c_str()), x, y); 
}
void ProgramManager::setVec3(size_t hashCode, std::string const &name, glm::vec3 value) { 
	if (this->program.count(hashCode))
	glUniform3fv(glGetUniformLocation(this->program[hashCode], name.c_str()), 1, &value[0]); 
}
void ProgramManager::setVec3(size_t hashCode, std::string const &name, float x, float y, float z) { 
	if (this->program.count(hashCode))
	glUniform3f(glGetUniformLocation(this->program[hashCode], name.c_str()), x, y, z); 
}
void ProgramManager::setVec4(size_t hashCode, std::string const &name, glm::vec4 value) { 
	if (this->program.count(hashCode))
	glUniform4fv(glGetUniformLocation(this->program[hashCode], name.c_str()), 1, &value[0]); 
}
void ProgramManager::setVec4(size_t hashCode, std::string const &name, float x, float y, float z, float w)  { 
	if (this->program.count(hashCode))
	glUniform4f(glGetUniformLocation(this->program[hashCode], name.c_str()), x, y, z, w); 
}
void ProgramManager::setMat3(size_t hashCode, std::string const &name, glm::mat3 &mat) {
	if (this->program.count(hashCode))
	glUniformMatrix3fv(glGetUniformLocation(this->program[hashCode], name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ProgramManager::setMat4(size_t hashCode, std::string const &name, glm::mat4 &mat) {
	if (this->program.count(hashCode))
	glUniformMatrix4fv(glGetUniformLocation(this->program[hashCode], name.c_str()), 1, GL_FALSE, &mat[0][0]);
}