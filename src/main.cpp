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

CGL::Mesh* getOpenBoxMesh() {
	CGL::Mesh* box = new CGL::Mesh();

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
		2, 1, 0,
		2, 3, 1,

		// 뒷면
		5, 6, 4,
		7, 6, 5,

		// 왼쪽 면
		3, 5, 1,
		3, 7, 5,

		// 오른쪽 면
		4, 2, 0,
		6, 2, 4,

		// 윗면
		1, 4, 0,
		5, 4, 1,

		// 아랫면
		6, 3, 2,
		6, 7, 3
	};
	box->setPosition(vertex);
	box->setIndex(index);
	box->setColors(glm::vec4(1, 1, 1, 1));
	box->setDrawType(CGL::DRAW_TRIANGLES);
	box->setScale(glm::vec3(5, 5, 5));
	box->setTranslate(glm::vec3(0, 0, 0));

	CGL::Material material;
	material.setAmbientColor(glm::vec3(0.8, 0.8, 0.8));
	material.setDiffuseColor(glm::vec3(0.8, 0.8, 0.8));
	material.setDiffuseColor(glm::vec3(0.8, 0.8, 0.8));
	material.setAlpha(1);
	material.setShininess(16);
	box->material = material;

	return box;
}

CGL::Mesh* getBoxMesh() {
	CGL::Mesh* box = new CGL::Mesh();

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
	box->setTranslate(glm::vec3(0, 0, 0));

	CGL::Material material;
	material.setAmbientColor(glm::vec3(0.1, 0.1, 0.1));
	material.setDiffuseColor(glm::vec3(0.1, 0.3, 0.1));
	material.setDiffuseColor(glm::vec3(0.1, 0.2, 0.1));
	material.setAlpha(1);
	material.setShininess(16);
	box->material = material;

	return box;
}

void setImGuiWindow(CGL::Scene& scene) {
	CGL::Device& device = CGL::Device::getInstance();

	static CGL::Mesh* curBox = nullptr;

	ImGui::Begin("Mesh Controller");

	ImGui::BeginGroup();
	if (ImGui::Button("Add Box Mesh")) {
		CGL::Mesh* box = getBoxMesh();
		scene.addObject(box);
		curBox = box;
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Box Mesh")) {
		scene.removeObject(curBox->getID());
		delete curBox;
		curBox = nullptr;
	}
	ImGui::EndGroup();

	if (curBox == nullptr) {
		ImGui::End();
		return;
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::BeginGroup();

	glm::vec4 origColor = curBox->getColors()[0];
	if (ImGui::ColorEdit4("Pick Color", (float*)&origColor)) {
		curBox->setColors(origColor);
	}

	// translate
	if (ImGui::Button("Translate : +x")) {
        // 값이 변경될 때 수행할 작업
        curBox->addTranslate(glm::vec3(1, 0, 0));
    }
	ImGui::SameLine();
	if (ImGui::Button("Translate : -x")) {
        // 값이 변경될 때 수행할 작업
        curBox->addTranslate(glm::vec3(-1, 0, 0));
    }
	ImGui::Spacing();
	if (ImGui::Button("Translate : +y")) {
        // 값이 변경될 때 수행할 작업
        curBox->addTranslate(glm::vec3(0, 1, 0));
    }
	ImGui::SameLine();
	if (ImGui::Button("Translate : -y")) {
        // 값이 변경될 때 수행할 작업
        curBox->addTranslate(glm::vec3(0, -1, 0));
    }
	ImGui::Spacing();
	if (ImGui::Button("Translate : +z")) {
        // 값이 변경될 때 수행할 작업
        curBox->addTranslate(glm::vec3(0, 0, 1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Translate : -z")) {
        // 값이 변경될 때 수행할 작업
        curBox->addTranslate(glm::vec3(0, 0, -1));
    }

	// rotate
	ImGui::Spacing();
	if (ImGui::Button("Rotate : +x")) {
        // 값이 변경될 때 수행할 작업
        curBox->addRotate(glm::vec3(1, 0, 0), 10);
    }
	ImGui::SameLine();
	if (ImGui::Button("Rotate : -x")) {
        // 값이 변경될 때 수행할 작업
        curBox->addRotate(glm::vec3(1, 0, 0), -10);
    }
	ImGui::Spacing();
	if (ImGui::Button("Rotate : +y")) {
        // 값이 변경될 때 수행할 작업
        curBox->addRotate(glm::vec3(0, 1, 0), 10);
    }
	ImGui::SameLine();
	if (ImGui::Button("Rotate : -y")) {
        // 값이 변경될 때 수행할 작업
        curBox->addRotate(glm::vec3(0, 1, 0), -10);
    }
	ImGui::Spacing();
	if (ImGui::Button("Rotate : +z")) {
        // 값이 변경될 때 수행할 작업
        curBox->addRotate(glm::vec3(0, 0, 1), 10);
    }
	ImGui::SameLine();
	if (ImGui::Button("Rotate : -z")) {
        // 값이 변경될 때 수행할 작업
        curBox->addRotate(glm::vec3(0, 0, 1), -10);
    }

	// scale
	ImGui::Spacing();
	if (ImGui::Button("Scale : +x")) {
        // 값이 변경될 때 수행할 작업
        curBox->addScale(glm::vec3(1.1, 1, 1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Scale : -x")) {
        // 값이 변경될 때 수행할 작업
        curBox->addScale(glm::vec3(0.9, 1, 1));
    }
	ImGui::Spacing();
	if (ImGui::Button("Scale : +y")) {
        // 값이 변경될 때 수행할 작업
        curBox->addScale(glm::vec3(1, 1.1, 1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Scale : -y")) {
        // 값이 변경될 때 수행할 작업
        curBox->addScale(glm::vec3(1, 0.9, 1));
    }
	ImGui::Spacing();
	if (ImGui::Button("Scale : +z")) {
        // 값이 변경될 때 수행할 작업
        curBox->addScale(glm::vec3(1, 1, 1.1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Scale : -z")) {
        // 값이 변경될 때 수행할 작업
        curBox->addScale(glm::vec3(1, 1, 0.9));
    }
	ImGui::EndGroup();
	
	ImGui::End();
}

void processMainRenderWork(CGL::Scene& scene, double& before, double& prevXPos, double& prevYPos) {
	CGL::Device& device = CGL::Device::getInstance();

	int width, height;
	glfwGetWindowSize(device.window, &width, &height);

	// get delta time
	double now = glfwGetTime();
	double delta = now - before;
	before = now;

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
			glfwGetKey(device.window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(device.window, GLFW_KEY_W) == GLFW_PRESS,
			glfwGetKey(device.window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(device.window, GLFW_KEY_S) == GLFW_PRESS,
			glfwGetKey(device.window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(device.window, GLFW_KEY_A) == GLFW_PRESS,
			glfwGetKey(device.window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(device.window, GLFW_KEY_D) == GLFW_PRESS,
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

void windowCloseCallback(GLFWwindow* window) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
	int width = 1080;
	int height = 720;

	CGL::Device& device = CGL::Device::getInstance();
	device.init();
	device.createWindow("hello", width, height);
	glfwGetWindowSize(device.window, &width, &height);
	glfwSetWindowCloseCallback(device.window, windowCloseCallback);

	CGL::Scene scene;

	CGL::ImguiDevice imguiDevice(device);

	CGL::Mesh* cor = new CGL::Mesh();
	CGL::Mesh* openBox = getOpenBoxMesh();
	CGL::Light* spotLight = new CGL::Light();
	CGL::Light* spotLight2 = new CGL::Light();
	CGL::Light* pointLight = new CGL::Light();
	CGL::PlayerCamera* camera = new CGL::PlayerCamera(glm::vec3(), glm::radians(180.f), 0, glm::radians(45.f), width, height);
	{
		{
			glPointSize(10);
			
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
		
		{
			spotLight->setLightType(CGL::LIGHT_SPOT);
			spotLight->setAmbientStrength(1);
			spotLight->setDiffuseStrength(1);
			spotLight->setSpecularStrength(1);
			spotLight->setAmbientcolor(glm::vec3(0, 0.3, 0));
			spotLight->setDiffusecolor(glm::vec3(0, 1, 0));
			spotLight->setSpecularcolor(glm::vec3(0, 0.1, 0));
			spotLight->setIntensity(0.8);
			spotLight->setConstantAttenuation(0.01);
			spotLight->setLinearAttenuation(0.01);
			spotLight->setQuadraticAttenuation(0.01);
			spotLight->setPosition(glm::vec3(0, 0, 0));
			spotLight->setEmitDirection(glm::vec3(0, -1, 0));
			spotLight->setInnerCutoff(glm::radians(20.f));
			spotLight->setOuterCutoff(glm::radians(45.f));
		}
		
		{
			spotLight2->setLightType(CGL::LIGHT_SPOT);
			spotLight2->setAmbientStrength(1);
			spotLight2->setDiffuseStrength(1);
			spotLight2->setSpecularStrength(1);
			spotLight2->setAmbientcolor(glm::vec3(0.3, 0, 0));
			spotLight2->setDiffusecolor(glm::vec3(1, 0, 0));
			spotLight2->setSpecularcolor(glm::vec3(0.1, 0, 0));
			spotLight2->setIntensity(0.8);
			spotLight2->setConstantAttenuation(0.01);
			spotLight2->setLinearAttenuation(0.01);
			spotLight2->setQuadraticAttenuation(0.01);
			spotLight2->setPosition(glm::vec3(0, 0, 0));
			spotLight2->setEmitDirection(glm::vec3(0, 1, 0));
			spotLight2->setInnerCutoff(glm::radians(20.f));
			spotLight2->setOuterCutoff(glm::radians(45.f));
		}
		
		{
			pointLight->setLightType(CGL::LIGHT_POINT);
			pointLight->setAmbientStrength(1);
			pointLight->setDiffuseStrength(1);
			pointLight->setSpecularStrength(1);
			pointLight->setAmbientcolor(glm::vec3(0.5, 0.5, 0.5));
			pointLight->setDiffusecolor(glm::vec3(0.7, 0.7, 0.7));
			pointLight->setSpecularcolor(glm::vec3(0.1, 0.1, 0.1));
			pointLight->setIntensity(0.8);
			pointLight->setConstantAttenuation(0.01);
			pointLight->setLinearAttenuation(0.01);
			pointLight->setQuadraticAttenuation(0.01);
			pointLight->setPosition(glm::vec3(0, 5, 0));
			pointLight->setEmitDirection(glm::vec3(0, 0, 0));
			pointLight->setInnerCutoff(glm::radians(20.f));
			pointLight->setOuterCutoff(glm::radians(45.f));
		}
		
		camera->setViewPosition(glm::vec3(0, 0, 3));
	}

	scene.addObject(cor);
	scene.addObject(openBox);
	scene.addObject(spotLight);
	scene.addObject(spotLight2);
	camera->addChild(pointLight);
	scene.addObject(camera);
	scene.setMainCamera(camera);

	glEnable(GL_CULL_FACE);

	bool moveMode = true;
	bool escPressed = false;

	device.setMouseMode(CGL::MouseType::MOUSE_HIDDEN);
	double before = glfwGetTime();
	double prevXPos;
	double prevYPos;
	{
		glfwSetCursorPos(device.window, width / 2, height / 2);
		glfwGetCursorPos(device.window, &prevXPos, &prevYPos);
	}
	while (!glfwWindowShouldClose(device.window)) {
		// loop begin process
		device.loopBeginProcess();

		if (!imguiDevice.getImGuiIO().WantCaptureMouse && moveMode) {
			processMainRenderWork(scene, before, prevXPos, prevYPos);
		}

		// render
		device.render(&scene);

        // GUI 구성
		if (!moveMode) {
			imguiDevice.loopBeginProcess();
			setImGuiWindow(scene);
			imguiDevice.loopEndProcess();
		}

		if (glfwGetKey(device.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			if (!escPressed) {
				moveMode = !moveMode;
				if (moveMode) {
					device.setMouseMode(CGL::MouseType::MOUSE_HIDDEN);
					glfwSetCursorPos(device.window, width / 2, height / 2);
				} else {
					device.setMouseMode(CGL::MouseType::MOUSE_NORMAL);
				}
				escPressed = true;
			}
		} else if (glfwGetKey(device.window, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
			escPressed = false;
		}

		// loop end process
		device.loopEndProcess();
	}
}