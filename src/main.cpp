#include <iostream>

#include "Scene.hpp"
#include "Mesh.hpp"
#include "PlayerCamera.hpp"
#include "ObjectCamera.hpp"
#include "Light.hpp"
#include "Device.hpp"
#include "Material.hpp"
#include "ImguiDevice.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

int main() {
	int width = 800;
	int height = 600;

	CGL::Device& device = CGL::Device::getInstance();
	device.init();
	device.createWindow("hello", width, height);
	glfwGetWindowSize(device.window, &width, &height);

	CGL::Scene scene;

	CGL::ImguiDevice imguiDevice(device);

	CGL::Mesh* cor = new CGL::Mesh();
	{
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec4> colors;
		for (int i = -100; i < 100; i++) {
			vertex.push_back(glm::vec3(i, 0, 0));
			vertex.push_back(glm::vec3(0, i, 0));
			vertex.push_back(glm::vec3(0, 0, i));

			colors.push_back(glm::vec4(i / std::abs(i), 0, 0, 1));
			colors.push_back(glm::vec4(0, i / std::abs(i), 0, 1));
			colors.push_back(glm::vec4(0, 0, i / std::abs(i), 1));
		}
		cor->setPosition(vertex);
		glm::vec4 color(1, 0, 0, 1);
		cor->setColors(colors);
		cor->setDrawType(CGL::DRAW_POINTS);
	}
	CGL::Mesh* floar = new CGL::Mesh();
	{
		std::vector<glm::vec3> vertex;
		vertex.push_back(glm::vec3(1, 1, 1));
		vertex.push_back(glm::vec3(-1, 1, 1));
		vertex.push_back(glm::vec3(1, -1, 1));
		vertex.push_back(glm::vec3(-1, -1, 1));
		vertex.push_back(glm::vec3(1, 1, -1));
		vertex.push_back(glm::vec3(-1, 1, -1));
		vertex.push_back(glm::vec3(1, -1, -1));
		vertex.push_back(glm::vec3(-1, -1, -1));

		std::vector<indice> index = {
			// 앞면
			0, 1, 2,
			1, 3, 2,

			// 뒷면
			4, 6, 5,
			5, 6, 7,

			// 왼쪽 면
			1, 5, 3,
			5, 7, 3,

			// 오른쪽 면
			0, 2, 4,
			4, 2, 6,

			// 윗면
			0, 4, 1,
			1, 4, 5,

			// 아랫면
			2, 3, 6,
			3, 7, 6
		};
		floar->setPosition(vertex);
		floar->setIndex(index);
		floar->setColors(glm::vec4(0.5, 0.5, 0.5, 1));
		floar->setDrawType(CGL::DRAW_TRIANGLES);
		floar->setScale(glm::vec3(10, 0.1, 10));
		floar->setTranslate(glm::vec3(0, -2, 0));

		CGL::Material material;
		material.setAmbientColor(glm::vec3(0.5, 0.5, 0.5));
		material.setDiffuseColor(glm::vec3(0.5, 0.5, 0.5));
		material.setDiffuseColor(glm::vec3(0.5, 0.5, 0.5));
		material.setAlpha(1);
		material.setShininess(32);
		floar->material = material;
	}
	CGL::Mesh* head1 = new CGL::Mesh();
	{
		std::vector<glm::vec3> vertex;
		vertex.push_back(glm::vec3(1, 1, 1));
		vertex.push_back(glm::vec3(-1, 1, 1));
		vertex.push_back(glm::vec3(1, -1, 1));
		vertex.push_back(glm::vec3(-1, -1, 1));
		vertex.push_back(glm::vec3(1, 1, -1));
		vertex.push_back(glm::vec3(-1, 1, -1));
		vertex.push_back(glm::vec3(1, -1, -1));
		vertex.push_back(glm::vec3(-1, -1, -1));

		std::vector<indice> index = {
			// 앞면
			0, 1, 2,
			1, 3, 2,

			// 뒷면
			4, 6, 5,
			5, 6, 7,

			// 왼쪽 면
			1, 5, 3,
			5, 7, 3,

			// 오른쪽 면
			0, 2, 4,
			4, 2, 6,

			// 윗면
			0, 4, 1,
			1, 4, 5,

			// 아랫면
			2, 3, 6,
			3, 7, 6
		};
		head1->setPosition(vertex);
		head1->setIndex(index);
		std::vector<glm::vec4> colors;

		colors.push_back(glm::vec4(0, 0.5, 0, 1));
		colors.push_back(glm::vec4(0, 0.5, 0, 1));
		colors.push_back(glm::vec4(0, 0.5, 0, 1));
		colors.push_back(glm::vec4(0, 0.5, 0, 1));
		colors.push_back(glm::vec4(0, 1, 0, 1));
		colors.push_back(glm::vec4(0, 1, 0, 1));
		colors.push_back(glm::vec4(0, 1, 0, 1));
		colors.push_back(glm::vec4(0, 1, 0, 1));

		head1->setColors(colors);
		head1->setDrawType(CGL::DRAW_TRIANGLES);
		// head1->setScale(glm::vec3(1, 1, 1));
		// head1->setTranslate(glm::vec3(0, 2, 0));
		CGL::Mesh* body1 = new CGL::Mesh();
		{
			std::vector<glm::vec3> vertex;
			vertex.push_back(glm::vec3(1, 1, 1));
			vertex.push_back(glm::vec3(-1, 1, 1));
			vertex.push_back(glm::vec3(1, -1, 1));
			vertex.push_back(glm::vec3(-1, -1, 1));
			vertex.push_back(glm::vec3(1, 1, -1));
			vertex.push_back(glm::vec3(-1, 1, -1));
			vertex.push_back(glm::vec3(1, -1, -1));
			vertex.push_back(glm::vec3(-1, -1, -1));

			std::vector<indice> index = {
				// 앞면
				0, 1, 2,
				1, 3, 2,

				// 뒷면
				4, 6, 5,
				5, 6, 7,

				// 왼쪽 면
				1, 5, 3,
				5, 7, 3,

				// 오른쪽 면
				0, 2, 4,
				4, 2, 6,

				// 윗면
				0, 4, 1,
				1, 4, 5,

				// 아랫면
				2, 3, 6,
				3, 7, 6
			};
			body1->setPosition(vertex);
			body1->setIndex(index);
			std::vector<glm::vec4> colors;

			colors.push_back(glm::vec4(0, 0.5, 0, 1));
			colors.push_back(glm::vec4(0, 0.5, 0, 1));
			colors.push_back(glm::vec4(0, 0.5, 0, 1));
			colors.push_back(glm::vec4(0, 0.5, 0, 1));
			colors.push_back(glm::vec4(0, 1, 0, 1));
			colors.push_back(glm::vec4(0, 1, 0, 1));
			colors.push_back(glm::vec4(0, 1, 0, 1));
			colors.push_back(glm::vec4(0, 1, 0, 1));

			body1->setColors(colors);
			body1->setDrawType(CGL::DRAW_TRIANGLES);
			body1->setScale(glm::vec3(1, 2, 0.5));
			body1->setTranslate(glm::vec3(0, -3, 0));
		}

		head1->addChild(body1);
	}
	CGL::Mesh* head2 = new CGL::Mesh();
	{
		std::vector<glm::vec3> vertex;
		vertex.push_back(glm::vec3(1, 1, 1));
		vertex.push_back(glm::vec3(-1, 1, 1));
		vertex.push_back(glm::vec3(1, -1, 1));
		vertex.push_back(glm::vec3(-1, -1, 1));
		vertex.push_back(glm::vec3(1, 1, -1));
		vertex.push_back(glm::vec3(-1, 1, -1));
		vertex.push_back(glm::vec3(1, -1, -1));
		vertex.push_back(glm::vec3(-1, -1, -1));

		std::vector<indice> index = {
			// 앞면
			0, 1, 2,
			1, 3, 2,

			// 뒷면
			4, 6, 5,
			5, 6, 7,

			// 왼쪽 면
			1, 5, 3,
			5, 7, 3,

			// 오른쪽 면
			0, 2, 4,
			4, 2, 6,

			// 윗면
			0, 4, 1,
			1, 4, 5,

			// 아랫면
			2, 3, 6,
			3, 7, 6
		};
		head2->setPosition(vertex);
		head2->setIndex(index);
		std::vector<glm::vec4> colors;

		colors.push_back(glm::vec4(0.5, 0.5, 0.5, 1));
		colors.push_back(glm::vec4(0.5, 0.5, 0.5, 1));
		colors.push_back(glm::vec4(0.5, 0.5, 0.5, 1));
		colors.push_back(glm::vec4(0.5, 0.5, 0.5, 1));
		colors.push_back(glm::vec4(1, 1, 1, 1));
		colors.push_back(glm::vec4(1, 1, 1, 1));
		colors.push_back(glm::vec4(1, 1, 1, 1));
		colors.push_back(glm::vec4(1, 1, 1, 1));

		head2->setColors(colors);
		head2->setDrawType(CGL::DRAW_TRIANGLES);
		CGL::Material material;
		material.setAmbientColor(glm::vec3(0, 0, 0.5));
		material.setDiffuseColor(glm::vec3(0, 0.5, 0));
		material.setDiffuseColor(glm::vec3(0, 1, 0));
		material.setAlpha(0.1);
		material.setShininess(16);
		head2->material = material;
	}
	CGL::Mesh* box = new CGL::Mesh();
	{
		std::vector<glm::vec3> vertex;
		vertex.push_back(glm::vec3(1, 1, 1));
		vertex.push_back(glm::vec3(-1, 1, 1));
		vertex.push_back(glm::vec3(1, -1, 1));
		vertex.push_back(glm::vec3(-1, -1, 1));
		vertex.push_back(glm::vec3(1, 1, -1));
		vertex.push_back(glm::vec3(-1, 1, -1));
		vertex.push_back(glm::vec3(1, -1, -1));
		vertex.push_back(glm::vec3(-1, -1, -1));

		std::vector<indice> index = {
			// 앞면
			0, 1, 2,
			1, 3, 2,

			// 뒷면
			4, 6, 5,
			5, 6, 7,

			// 왼쪽 면
			1, 5, 3,
			5, 7, 3,

			// 오른쪽 면
			0, 2, 4,
			4, 2, 6,

			// 윗면
			0, 4, 1,
			1, 4, 5,

			// 아랫면
			2, 3, 6,
			3, 7, 6
		};
		box->setPosition(vertex);
		box->setIndex(index);
		box->setColors(glm::vec4(1, 1, 1, 1));
		box->setDrawType(CGL::DRAW_TRIANGLES);
		box->setScale(glm::vec3(0.5, 0.5, 0.5));
		box->setTranslate(glm::vec3(0, 0, -10));

		CGL::Material material;
		material.setAmbientColor(glm::vec3(0, 0, 0.5));
		material.setDiffuseColor(glm::vec3(0, 0.5, 0));
		material.setDiffuseColor(glm::vec3(0, 1, 0));
		material.setAlpha(0.5);
		material.setShininess(16);
		box->material = material;
	}
	CGL::Light* lightObj = new CGL::Light();
	{
		lightObj->setLightType(CGL::LIGHT_POINT);
		lightObj->setAmbientStrength(1);
		lightObj->setDiffuseStrength(1);
		lightObj->setSpecularStrength(1);
		lightObj->setAmbientcolor(glm::vec3(1, 0.8, 0.8));
		lightObj->setDiffusecolor(glm::vec3(1, 0.8, 0.8));
		lightObj->setSpecularcolor(glm::vec3(1, 0.8, 0.8));
		lightObj->setIntensity(0.8);
		lightObj->setConstantAttenuation(0.01);
		lightObj->setLinearAttenuation(0.01);
		lightObj->setQuadraticAttenuation(0.01);
		lightObj->setPosition(glm::vec3(0, 5, 0));
		lightObj->setEmitDirection(glm::vec3(0, -1, 0));
		lightObj->setInnerCutoff(glm::radians(30.f));
		lightObj->setOuterCutoff(glm::radians(45.f));

		CGL::Mesh* lightBox = new CGL::Mesh();
		{
			std::vector<glm::vec3> vertex;
			vertex.push_back(glm::vec3(1, 1, 1));
			vertex.push_back(glm::vec3(-1, 1, 1));
			vertex.push_back(glm::vec3(1, -1, 1));
			vertex.push_back(glm::vec3(-1, -1, 1));
			vertex.push_back(glm::vec3(1, 1, -1));
			vertex.push_back(glm::vec3(-1, 1, -1));
			vertex.push_back(glm::vec3(1, -1, -1));
			vertex.push_back(glm::vec3(-1, -1, -1));

			std::vector<indice> index = {
				// 앞면
				0, 1, 2,
				1, 3, 2,

				// 뒷면
				4, 6, 5,
				5, 6, 7,

				// 왼쪽 면
				1, 5, 3,
				5, 7, 3,

				// 오른쪽 면
				0, 2, 4,
				4, 2, 6,

				// 윗면
				0, 4, 1,
				1, 4, 5,

				// 아랫면
				2, 3, 6,
				3, 7, 6
			};
			lightBox->setPosition(vertex);
			lightBox->setIndex(index);
			lightBox->setColors(lightObj->getSpecularcolor());
			lightBox->setDrawType(CGL::DRAW_TRIANGLES);
			lightBox->setScale(glm::vec3(0.1, 0.1, 0.1));
		}

		lightObj->addChild(lightBox);
	}
	CGL::ObjectCamera* camera1 = new CGL::ObjectCamera(glm::vec3(), glm::radians(180.f), 0, glm::radians(45.f), width, height);
	camera1->setViewPosition(glm::vec3(10, 10, 10));
	CGL::PlayerCamera* camera2 = new CGL::PlayerCamera(glm::vec3(), glm::radians(180.f), 0, glm::radians(45.f), width, height);

	scene.addObject(cor);
	scene.addObject(lightObj);
	scene.addObject(floar);
	scene.addObject(box);
	scene.addObject(camera1);
	scene.addObject(camera2);
	camera1->addChild(head1);
	camera2->addChild(head2);
	scene.setMainCamera(camera1);

	glPointSize(10);
	double before = glfwGetTime();

	glEnable(GL_CULL_FACE);

	double prevXPos;
	double prevYPos;
	{
		glfwSetCursorPos(device.window, width / 2, height / 2);
		glfwGetCursorPos(device.window, &prevXPos, &prevYPos);
	}
	while (1) {
		// loop begin process
		device.loopBeginProcess();
		imguiDevice.loopBeginProcess();

        // GUI 구성
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a simple text");
        ImGui::End();

		// get delta time
		double now = glfwGetTime();
		double delta = now - before;
		before = now;

		// camera update
		{
			CGL::ICamera* camera = scene.getMainCamera();
			
			if (dynamic_cast<CGL::PlayerCamera*>(camera) != nullptr) {
				double xPos, yPos;
				glfwGetCursorPos(device.window, &xPos, &yPos);
				glfwSetCursorPos(device.window, width / 2, height / 2);

				double xDelta = ((width / 2) - xPos);
				double yDelta = ((height / 2) - yPos);
				
				CGL::PlayerCamera* playerCamera = dynamic_cast<CGL::PlayerCamera*>(camera);
				playerCamera->loopCamera(
					delta,
					glfwGetKey(device.window, GLFW_KEY_UP) == GLFW_PRESS,
					glfwGetKey(device.window, GLFW_KEY_DOWN) == GLFW_PRESS,
					glfwGetKey(device.window, GLFW_KEY_LEFT) == GLFW_PRESS,
					glfwGetKey(device.window, GLFW_KEY_RIGHT) == GLFW_PRESS,
					xDelta, yDelta
				);
			} else if (dynamic_cast<CGL::ObjectCamera*>(camera) != nullptr) {
				double xPos, yPos;
				glfwGetCursorPos(device.window, &xPos, &yPos);

				CGL::ObjectCamera* objectCamera = dynamic_cast<CGL::ObjectCamera*>(camera);
				objectCamera->loopCamera(
					glfwGetMouseButton(device.window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS,
					glfwGetMouseButton(device.window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS,
					xPos - prevXPos,
					yPos - prevYPos
				);

				prevXPos = xPos;
				prevYPos = yPos;
			}
		}

		// key event
		{
			if (glfwGetKey(device.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				exit(0);
			if (glfwGetKey(device.window, GLFW_KEY_1) == GLFW_PRESS)
				scene.setMainCamera(camera1);
			if (glfwGetKey(device.window, GLFW_KEY_2) == GLFW_PRESS)
				scene.setMainCamera(camera2);
		}

		// render
		device.render(&scene);

		// loop end process
		imguiDevice.loopEndProcess();
		device.loopEndProcess();
	}
}