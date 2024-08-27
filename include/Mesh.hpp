#ifndef MESH_HPP
#define MESH_HPP

#include "pch.hpp"

#include "IResourceID.hpp"
#include "Device.hpp"

class Mesh : private IResourceID {
	private:
		Device* device;

		Mesh *parent;
		std::vector<Mesh*> children;
		
		glm::mat4 model;

		glm::mat4 scaleMat;
		glm::mat4 rotateMat;
		glm::mat4 translateMat;

		std::vector<glm::vec3> vertex;
		std::vector<uint> index;
		std::vector<glm::vec3> normal;
		std::vector<glm::vec2> UV;

		glm::vec4 color;
	public:
		Mesh(Device* device, Mesh *parent = nullptr);
		virtual ~Mesh();
		Mesh(const Mesh&) = delete;
    	Mesh& operator=(const Mesh&) = delete;

		void addChild(Mesh* child);

		// update member var
		void setVertex(std::vector<glm::vec3> &vertex);
		void setIndex(std::vector<uint> &index);
		void setNormal(std::vector<glm::vec3> &normal);
		void setUV(std::vector<glm::vec2> &UV);
		
		void setColor(glm::vec4 color);

		void modelInit();
		void setScale(glm::vec3 size);
		void setRotate(float angle, glm::vec3 axis);
		void setTranslate(glm::vec3 pos);
		glm::mat4& getModel();

		// update buffer
		void updateBuffer();

		void test();

	private:
};

#endif