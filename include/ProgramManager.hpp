#ifndef PROGRAMMANAGER_HPP
#define PROGRAMMANAGER_HPP

#include "pch.hpp"

#include "ShaderLoader.hpp"

enum ShaderType {
	VERTEX_SHADER,
	TESS_CONTROL_SHADER,
	TESS_EVALUATION_SHADER,
	GEOMETRY_SHADER,
	FRAGMENT_SHADER,
	COMPUTE_SHADER
};

class ProgramManager {
	private:
		std::unordered_map<size_t, GLuint> program;
		
	public:
		ProgramManager();
		~ProgramManager();

		GLuint getProgram(
			std::unordered_map<ShaderType, std::string> &shader,
			std::set<std::string> &define
		);

		void useProgram(size_t hashCode);

		std::vector<GLuint> getAllPrograms();

	private:
		GLuint loadShader(ShaderType shaderType, std::string const &fileName, std::set<std::string> &define);

		size_t loadProgram(
			std::unordered_map<ShaderType, std::string> &shader,
			std::set<std::string> &define
		);

		size_t getHash(
			std::unordered_map<ShaderType, std::string> &shader,
			std::set<std::string> &define
		);

		GLuint getID(size_t hashCode);
	
	public: // uniform function
		void setBool(size_t hashCode, std::string const &name, bool value);
		void setInt(size_t hashCode, std::string const &name, int value);
		void setFloat(size_t hashCode, std::string const &name, float value);
		void setVec2(size_t hashCode, std::string const &name, glm::vec2 value);
		void setVec2(size_t hashCode, std::string const &name, float x, float y);
		void setVec3(size_t hashCode, std::string const &name, glm::vec3 value);
		void setVec3(size_t hashCode, std::string const &name, float x, float y, float z);
		void setVec4(size_t hashCode, std::string const &name, glm::vec4 value);
		void setVec4(size_t hashCode, std::string const &name, float x, float y, float z, float w);
		void setMat3(size_t hashCode, std::string const &name, glm::mat3 &mat);
		void setMat4(size_t hashCode, std::string const &name, glm::mat4 &mat);
};

#endif