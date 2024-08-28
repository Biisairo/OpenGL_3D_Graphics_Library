#include "ProgramManager.hpp"

ProgramManager::ProgramManager() {
	for (int i = VERTEX_SHADER; i <= COMPUTE_SHADER; i++)
		shader[static_cast<ShaderType>(i)] = std::map<std::string, GLuint>();
}

ProgramManager::~ProgramManager() {
	for (int i = VERTEX_SHADER; i <= COMPUTE_SHADER; i++) {
		for (std::map<std::string, GLuint>::iterator it = this->shader[static_cast<ShaderType>(i)].begin();
			it != this->shader[static_cast<ShaderType>(i)].end(); it++) {
			glDeleteShader(it->second);
		}
	}

	for (std::map<std::string, GLuint>::iterator it = this->program.begin();
		it != this->program.end(); it++) {
		glDeleteProgram(it->second);
	}
}

bool ProgramManager::loadShader(ShaderType shaderType, std::string const &shaderName, std::string const &filename) {
	std::fstream file;
	file.open(filename);
	if (!file.is_open()) {
		std::cerr << filename << " not open" << std::endl;
		return false;
	}
	std::string str;
	file.seekg(0,std::ios::end);
	size_t size = file.tellg();
	str.resize(size);
	file.seekg(0, std::ios::beg);
	file.read(&str[0], size);
	file.close();

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
	const GLchar *source = str.c_str();
	const GLint length = str.length();
	glShaderSource(id, 1, &source, &length);

	glCompileShader(id);

	GLint check;
	glGetShaderiv(id, GL_COMPILE_STATUS, &check);
	if (check == GL_FALSE) {
		glDeleteShader(id);
		std::cerr << filename << " not compiled" << std::endl;
		return false;
	};

	this->shader[shaderType].insert(std::make_pair(shaderName, id));
	return true;
}

void ProgramManager::deleteShader(ShaderType shaderType, std::string const &shaderName) {
	glDeleteShader(this->shader[shaderType][shaderName]);
	this->shader[shaderType].erase(shaderName);
}

bool ProgramManager::loadProgram(
	std::string const &programName,
	std::string const &vertexShader,
	std::string const &tessControlShader,
	std::string const &tessEvaluationShader,
	std::string const &geometryShader,
	std::string const &fragmentShader,
	std::string const &computeShader
) {
	GLuint id = glCreateProgram();

	if (this->shader[VERTEX_SHADER].count(vertexShader))
			glAttachShader(id, this->shader[VERTEX_SHADER][vertexShader]);
	if (this->shader[TESS_CONTROL_SHADER].count(vertexShader))
			glAttachShader(id, this->shader[TESS_CONTROL_SHADER][vertexShader]);
	if (this->shader[TESS_EVALUATION_SHADER].count(vertexShader))
			glAttachShader(id, this->shader[TESS_EVALUATION_SHADER][vertexShader]);
	if (this->shader[GEOMETRY_SHADER].count(vertexShader))
			glAttachShader(id, this->shader[GEOMETRY_SHADER][vertexShader]);
	if (this->shader[FRAGMENT_SHADER].count(vertexShader))
			glAttachShader(id, this->shader[FRAGMENT_SHADER][vertexShader]);
	if (this->shader[COMPUTE_SHADER].count(vertexShader))
			glAttachShader(id, this->shader[COMPUTE_SHADER][vertexShader]);

	glLinkProgram(id);

	if (this->shader[VERTEX_SHADER].count(vertexShader))
			glDetachShader(id, this->shader[VERTEX_SHADER][vertexShader]);
	if (this->shader[TESS_CONTROL_SHADER].count(vertexShader))
			glDetachShader(id, this->shader[TESS_CONTROL_SHADER][vertexShader]);
	if (this->shader[TESS_EVALUATION_SHADER].count(vertexShader))
			glDetachShader(id, this->shader[TESS_EVALUATION_SHADER][vertexShader]);
	if (this->shader[GEOMETRY_SHADER].count(vertexShader))
			glDetachShader(id, this->shader[GEOMETRY_SHADER][vertexShader]);
	if (this->shader[FRAGMENT_SHADER].count(vertexShader))
			glDetachShader(id, this->shader[FRAGMENT_SHADER][vertexShader]);
	if (this->shader[COMPUTE_SHADER].count(vertexShader))
			glDetachShader(id, this->shader[COMPUTE_SHADER][vertexShader]);

	// check link done
	GLint check;
	glGetProgramiv(id, GL_LINK_STATUS, &check);
	if (check == GL_FALSE) {
		glDeleteProgram(id);
		std::cerr << "Program does not linked" << std::endl;
		return false;
	}

	this->program[programName] = id;

	return true;
}

void ProgramManager::setBool(std::string const &programName, std::string const &name, bool value) {         
	if (this->program.count(programName))
	glUniform1i(glGetUniformLocation(this->program[programName], name.c_str()), (int)value); 
}
void ProgramManager::setInt(std::string const &programName, std::string const &name, int value) { 
	if (this->program.count(programName))
	glUniform1i(glGetUniformLocation(this->program[programName], name.c_str()), value); 
}
void ProgramManager::setFloat(std::string const &programName, std::string const &name, float value) { 
	if (this->program.count(programName))
	glUniform1f(glGetUniformLocation(this->program[programName], name.c_str()), value); 
}
void ProgramManager::setVec2(std::string const &programName, std::string const &name, glm::vec2 value) { 
	if (this->program.count(programName))
	glUniform2fv(glGetUniformLocation(this->program[programName], name.c_str()), 1, &value[0]); 
}
void ProgramManager::setVec2(std::string const &programName, std::string const &name, float x, float y) { 
	if (this->program.count(programName))
	glUniform2f(glGetUniformLocation(this->program[programName], name.c_str()), x, y); 
}
void ProgramManager::setVec3(std::string const &programName, std::string const &name, glm::vec3 value) { 
	if (this->program.count(programName))
	glUniform3fv(glGetUniformLocation(this->program[programName], name.c_str()), 1, &value[0]); 
}
void ProgramManager::setVec3(std::string const &programName, std::string const &name, float x, float y, float z) { 
	if (this->program.count(programName))
	glUniform3f(glGetUniformLocation(this->program[programName], name.c_str()), x, y, z); 
}
void ProgramManager::setVec4(std::string const &programName, std::string const &name, glm::vec4 value) { 
	if (this->program.count(programName))
	glUniform4fv(glGetUniformLocation(this->program[programName], name.c_str()), 1, &value[0]); 
}
void ProgramManager::setVec4(std::string const &programName, std::string const &name, float x, float y, float z, float w)  { 
	if (this->program.count(programName))
	glUniform4f(glGetUniformLocation(this->program[programName], name.c_str()), x, y, z, w); 
}
void ProgramManager::setMat3(std::string const &programName, std::string const &name, glm::mat3 &mat) {
	if (this->program.count(programName))
	glUniformMatrix3fv(glGetUniformLocation(this->program[programName], name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void ProgramManager::setMat4(std::string const &programName, std::string const &name, glm::mat4 &mat) {
	if (this->program.count(programName))
	glUniformMatrix4fv(glGetUniformLocation(this->program[programName], name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ProgramManager::useProgram(std::string const &programName) {
	if (this->program.count(programName))
	glUseProgram(this->program[programName]);
}

GLuint ProgramManager::getID(std::string const &programName) {
	if (this->program.count(programName))
		return this->program[programName];
	return 0;
}