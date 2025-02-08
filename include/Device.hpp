#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include <sstream>

#include "Extern/GLMHeader.hpp"
#include "Extern/OpenGLHeader.hpp"

#include "FramebufferManager.hpp"
#include "IResourceID.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "ICamera.hpp"

#define MAX_LIGHT_COUNT 10

using programHash = size_t;

namespace CGL {

	namespace SHADER_FILE {
		constexpr const char* SHADER_PATH = "../src/shader/";

		constexpr const char* COMMON_SHADER_VERT = "vs/CameraNormal.vert";
		constexpr const char* COMMON_SHADER_FRAG = "fs/CameraNormal.frag";

		constexpr const char* SHADOW_SHADER_VERT = "vs/Shadow.vert";
		constexpr const char* SHADOW_SHADER_FRAG = "fs/Shadow.frag";

		constexpr const char* DEFAULT_SHADER_VERT = "vs/default.vert";
		constexpr const char* DEFAULT_SHADER_FRAG = "fs/default.frag";

		constexpr const char* NORMAL_CHECK_SHADER_VERT = "vs/checkNormal.vert";
		constexpr const char* NORMAL_CHECK_SHADER_GEO = "gs/checkNormal.geom";
		constexpr const char* NORMAL_CHECK_SHADER_FRAG = "fs/checkNormal.frag";

		constexpr const char* SHADOW_TEST_VERT = "vs/ShadowTest.vert";
		constexpr const char* SHADOW_TEST_FRAG = "fs/ShadowTest.frag";
	}

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
	struct MaterialBuffer {
		glm::vec4 ambientColor;
		glm::vec4 diffuseColor;
		glm::vec4 specularColor;

		float alpha;
		float shininess;
	};

	struct MeshBuffer {
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		unsigned int count;
		programHash program;
		DrawType drawType;
		MaterialBuffer materialBuffer;
	};

	struct alignas(16) LightBuffer {
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

		glm::mat4 projection;
		glm::mat4 view;
		glm::vec4 position;
		
		// only for emitType 2, spotlight
		glm::vec4 emitDirection;
		float innerCutoff;
		float outerCutoff;
	};

	struct LightBuffers {
		uint lightCount = 0;
		std::vector<LightBuffer> light;
	};

	struct UniformBlock {
		GLuint uniformBlockBuffer;
		std::unordered_map<GLuint, GLuint> uniformBlockIndex;
	};

	class Device {
		public:
			GLFWwindow* window = nullptr;
		private:
			
			std::unordered_map<objectID, MeshBuffer> meshes;
			
			std::unordered_map<std::string, UniformBlock> uniformBlocks;
			std::unordered_map<std::string, GLuint> uniformBufferIndexMap;
			
			std::unordered_map<programHash, GLuint> programs;

			FramebufferManager framebufferManager;
			std::string defaultRenderFramebufferName;

			bool isRenderShadow = false;
			bool isCheckNormal = false;

		// device
		public:
			Device(const Device& other) = delete;
			Device& operator=(const Device& other) = delete;

			static Device& getInstance();
			void init();
			void createWindow(std::string const &title, int width, int height);
			void initDefaultOpenGLParameter();
			void initDefaultTextureParameter();
			void setupFrameBuffer();

			void loopBeginProcess();
			void loopEndProcess();

			void getError();

			void setMouseMode(MouseType mouseType);

			void render(Scene* scene);
			
		private:
			Device();
			~Device();

			void getMeshes(IObject3D* object, std::vector<CGL::Mesh*>& meshes);
			void registerMeshes(std::vector<CGL::Mesh*>& meshes);
			void drawMeshes(std::vector<Mesh*>& meshes);
			void drawNormals(std::vector<Mesh*>& meshes);

			void getLights(IObject3D* object, std::vector<Light*>& lights);
			LightBuffers trimLights(std::vector<Light*>& lights);
			void registerLights(LightBuffers& lightBuffers);

			void registerLightView(LightBuffer& lightBuffer);

			void drawShadows(std::vector<Mesh*>& meshes);

			void registerCamera(ICamera* camera);

			void drawMesh(objectID ID, glm::mat4 model);
			void drawShadow(objectID ID, glm::mat4 model);
			void drawNormal(objectID ID, glm::mat4 model);
		public:
			void renderShadow(bool isRenderShadow);
			void renderNormal(bool isCheckNormal);

		private:
			void drawFrameBuffer(std::string frameBufferName);
			void drawShadowBuffer(std::string frameBufferName, bool isPerspective);

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
				CGL::DrawType drawType,
				glm::vec4 ambientColor,
				glm::vec4 diffuseColor,
				glm::vec4 specularColor,
				float alpha,
				float shininess
			);
			void deleteMesh(objectID ID);

		// uniform
		public:
			void addUniformBlock(std::string const &uniformBlockName);
			void registerUniformBlock(std::string const &uniformBlockName, std::vector<GLuint> &programs);
			GLuint getUniformBlockBuffer(std::string const &uniformBlockName);
			void deleteUniformBlock(std::string const &uniformBlockName);
			void useUniformBlock(std::string const &uniformBlockName);
			void unuseUniformBlock();
			GLuint getBindingIndex(std::string const &uniformBlockName);
			void useHDR(bool isUseHDR);

		// programs
		public:
			programHash getProgram(
				std::unordered_map<ShaderType, std::string> &shader,
				std::set<std::string> &define
			);
			void useProgram(programHash hashCode);
			std::vector<GLuint> getAllPrograms();
			std::vector<programHash> getAllProgramHashes();

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