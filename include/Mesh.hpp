#ifndef MESH_HPP
#define MESH_HPP

#include "pch.hpp"

#include "IResourceID.hpp"
#include "Device.hpp"

enum TextureType {
	TEXTURE_DIFFUSE,
	TEXTURE_NORMAL,
	TEXTURE_SPECULAR,
	TEXTURE_ALPHA,
	TEXTURE_LIGHT_MAP,
	TEXTURE_SHADOW_MAP,
	TEXTURE_ENV_MAP,
	TEXTURE_SKYBOX,
	TEXTURE_DISPLACEMENT_MAP,
	TEXTURE_HEIGHT_MAP,
	TEXTURE_RANDER_TARGET,
	TEXTURE_TEXTURE_ARRAY,
	TEXTURE_3D
};

class Mesh : private IResourceID {
	private:
		Device* device;

		Mesh *parent;
		std::vector<Mesh*> children;
		
		glm::mat4 model;
		std::vector<glm::mat4> instancing;

		glm::mat4 scaleMat;
		glm::mat4 rotateMat;
		glm::mat4 translateMat;

		std::vector<glm::vec3> position;
		std::vector<glm::vec3> normal;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> tangent;
		std::vector<glm::vec3> bitangent;
		std::vector<glm::vec4> colors;
		std::vector<GLuint> index;

	public:
		Mesh(Device* device, Mesh *parent = nullptr);
		virtual ~Mesh();
		Mesh(const Mesh&) = delete;
    	Mesh& operator=(const Mesh&) = delete;

		void addChild(Mesh* child);

		// update member var
		void setPosition (std::vector<glm::vec3> &position);
		void setNormal (std::vector<glm::vec3> &normal);
		void setTexCoords (std::vector<glm::vec2> &texCoords);
		void setTangent (std::vector<glm::vec3> &tangent);
		void setBitangent (std::vector<glm::vec3> &bitangent);
		void setColors (std::vector<glm::vec4> &colors);
		void setColors (glm::vec4 &color);
		void setIndex (std::vector<GLuint> &index);
		void setVertexData();

		void modelInit();
		void setInstancing(std::vector<glm::mat4> &instancing);
		void setScale(glm::vec3 size);
		void setRotate(float angle, glm::vec3 axis);
		void setTranslate(glm::vec3 pos);
		glm::mat4& getModel();

		// update buffer
		void updateBuffer();

	private:
		void makeNormal();
		void makeTangentSpace();
};

#endif