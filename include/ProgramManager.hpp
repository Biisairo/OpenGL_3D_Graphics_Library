#ifndef PROGRAMMANAGER_HPP
#define PROGRAMMANAGER_HPP

#include "pch.hpp"

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
		std::map<ShaderType, std::map<std::string, GLuint>> shader;
		std::map<std::string, GLuint> program;
		
	public:
		ProgramManager();
		~ProgramManager();

		bool loadShader(ShaderType shaderType, std::string const &shaderName, std::string const &filename);
		void deleteShader(ShaderType shaderType, std::string const &shaderName);

		bool loadProgram(
			std::string const &programName,
			std::string const &vertexShader,
			std::string const &tessControlShader,
			std::string const &tessEvaluationShader,
			std::string const &geometryShader,
			std::string const &fragmentShader,
			std::string const &computeShader
		);

		void setBool(std::string const &programName, std::string const &name, bool value);
		void setInt(std::string const &programName, std::string const &name, int value);
		void setFloat(std::string const &programName, std::string const &name, float value);
		void setVec2(std::string const &programName, std::string const &name, glm::vec2 value);
		void setVec2(std::string const &programName, std::string const &name, float x, float y);
		void setVec3(std::string const &programName, std::string const &name, glm::vec3 value);
		void setVec3(std::string const &programName, std::string const &name, float x, float y, float z);
		void setVec4(std::string const &programName, std::string const &name, glm::vec4 value);
		void setVec4(std::string const &programName, std::string const &name, float x, float y, float z, float w);
		void setMat3(std::string const &programName, std::string const &name, glm::mat3 &mat);
		void setMat4(std::string const &programName, std::string const &name, glm::mat4 &mat);

		void useProgram(std::string const &programName);
		GLuint getID(std::string const &programName);
};

#endif