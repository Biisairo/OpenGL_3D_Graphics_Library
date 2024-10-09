#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include <sstream>

#include "Extern/GLMHeader.hpp"
#include "Extern/OpenGLHeader.hpp"

#include "IResourceID.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"
#include "Light.hpp"

#define SHADER_PATH "../src/shader/"

// #define COMMON_SHADER_VERT "vs/test.vert"
// #define COMMON_SHADER_FRAG "fs/test.frag"
#define COMMON_SHADER_VERT "vs/CameraNormal.vert"
#define COMMON_SHADER_FRAG "fs/CameraNormal.frag"

#define MAX_LIGHT_COUNT 100

using programHash = size_t;

namespace CGL {

	// enum
	enum MouseType {
		MOUSE_NORMAL,
		MOUSE_HIDDEN,
		MOUSE_DISABLED,
		MOUSE_CAPTURED
	};

	enum ShaderType {
		VERTEX_SHADER,
		TESS_CONTROL_SHADER,
		TESS_EVALUATION_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		COMPUTE_SHADER
	};

	// struct
	struct MeshBuffer {
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		unsigned int count;
		programHash program;
		DrawType drawType;
	};

	struct LightBuffer {
		uint emitType;
		// 0 directional light
		// 1 point light
		// 2 spot light

		float ambientStrength;
		float diffuseStrength;
		float specularStrength;

		glm::vec4 ambientcolor;
		glm::vec4 diffusecolor;
		glm::vec4 specularcolor;

		// 강도
		float intensity;

		// 감쇄 상수
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
		// (1 / constant + linear × d + quadratic × d x d), d 는 거리

		// multiple minus when directional light
		glm::vec4 position;

		// only for emitType 2, spotlight
		glm::vec4 emitDirection;
		float innerCutoff;
		float outerCutoff;
		
		// padding
		float padding[2]{0, 0};
	};

	struct LightBuffers {
		uint lightCount;
		std::vector<LightBuffer> light;
	};

	struct UniformBlock {
		GLuint uniformBlockBuffer;
		std::unordered_map<GLuint, GLuint> uniformBlockIndex;
	};

	class Device {
		public:
			GLFWwindow* window;
		private:
			
			std::unordered_map<objectID, MeshBuffer> meshes;
			std::unordered_map<std::string, UniformBlock> uniformBlocks;
			std::unordered_map<programHash, GLuint> programs;

		// device
		public:
			Device(const Device& other) = delete;
			Device& operator=(const Device& other) = delete;

			static Device& getInstance();
			void init();
			void createWindow(std::string const &title, int width, int height);

			void loopBeginProcess();
			void loopEndProcess();

			void getError();

			void setMouseMode(MouseType mouseType);

			void render(Scene* scene);
			void registerCamera(Camera* camera);
			void recursiveRegisterMesh(IObject3D* object);
			void registerLight(LightBuffers& lightBuffers);
			void recursiveRegisterLight(CGL::IObject3D* object, LightBuffers& lightBuffers);
			void recursiveDraw(IObject3D* object);

		private:
			Device();
			~Device();

		// mesh
		public:
			void updateMesh(
				objectID ID,
				std::vector<glm::vec3> position,
				std::vector<glm::vec3> normal,
				std::vector<glm::vec2> texCoords,
				std::vector<glm::vec3> tangent,
				std::vector<glm::vec3> bitangent,
				std::vector<glm::vec4> colors,
				std::vector<uint> index,
				CGL::DrawType drawType
			);
			// void updateMesh(texture);
			void deleteMesh(objectID ID);
			void draw(objectID ID, glm::mat4 model);

		// uniform
		public:
			void addUniformBlock(std::string const &uniformBlockName, std::vector<GLuint> &programs);
			GLuint getUniformBlockBuffer(std::string const &uniformBlockName);
			void deleteUniformBlock(std::string const &uniformBlockName);
			void useUniformBlock(std::string const &uniformBlockName);
			void unuseUniformBlock();
			GLuint getBindingIndex(std::string const &uniformBlockName);


		// programs
		public:
			programHash getProgram(
				std::unordered_map<ShaderType, std::string> &shader,
				std::set<std::string> &define
			);
			void useProgram(programHash hashCode);
			std::vector<GLuint> getAllPrograms();

			void setBool(programHash hashCode, std::string const &name, bool value);
			void setInt(programHash hashCode, std::string const &name, int value);
			void setFloat(programHash hashCode, std::string const &name, float value);
			void setVec2(programHash hashCode, std::string const &name, glm::vec2 value);
			void setVec2(programHash hashCode, std::string const &name, float x, float y);
			void setVec3(programHash hashCode, std::string const &name, glm::vec3 value);
			void setVec3(programHash hashCode, std::string const &name, float x, float y, float z);
			void setVec4(programHash hashCode, std::string const &name, glm::vec4 value);
			void setVec4(programHash hashCode, std::string const &name, float x, float y, float z, float w);
			void setMat3(programHash hashCode, std::string const &name, glm::mat3 &mat);
			void setMat4(programHash hashCode, std::string const &name, glm::mat4 &mat);
		
		private:
			GLuint loadShader(ShaderType shaderType, std::string const &fileName, std::set<std::string> &define);

			programHash loadProgram(
				std::unordered_map<ShaderType, std::string> &shader,
				std::set<std::string> &define
			);

			programHash getProgramHash(
				std::unordered_map<ShaderType, std::string> &shader,
				std::set<std::string> &define
			);

			GLuint getProgramID(programHash hashCode);
	};

	static void error_callback(int error, const char *des);
	static std::string loadShaderCode(std::string const &fileName);

} // namespace CGL

#endif