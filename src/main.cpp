#include <iostream>

#include "Scene.hpp"
#include "Mesh.hpp"
#include "PlayerCamera.hpp"
#include "ObjectCamera.hpp"
#include "Light.hpp"
#include "Device.hpp"
#include "Material.hpp"
#include "ImguiDevice.hpp"

#define WIDTH 1080
#define HEIGHT 720

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
	box->setScale(glm::vec3(20, 20, 20));
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
	material.setDiffuseColor(glm::vec3(0.2, 0.2, 0.2));
	material.setSpecularColor(glm::vec3(0.1, 0.1, 0.1));
	material.setAlpha(1);
	material.setShininess(16);
	box->material = material;

	return box;
}

void setImGuiWindow(CGL::Scene& scene, std::vector<CGL::Mesh*>& meshes) {
	static int idx = -1;

	CGL::Device& device = CGL::Device::getInstance();

	ImGui::Begin("Mesh Controller");

	ImGui::BeginGroup();
	if (ImGui::Button("Add Box Mesh")) {
		CGL::Mesh* box = getBoxMesh();
		scene.addObject(box);
		meshes.push_back(box);
		idx = meshes.size() - 1;
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete Box Mesh") && idx != -1) {
		CGL::Mesh* box = meshes[idx];
		scene.removeObject(box->getID());
		meshes.erase(meshes.begin() + idx);
		delete meshes[idx];
		idx = meshes.size() - 1;
	}
	ImGui::EndGroup();

	if (idx == -1) {
		ImGui::End();
		return;
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	ImGui::BeginGroup();

	glm::vec4 origColor = meshes[idx]->getColors()[0];
	if (ImGui::ColorEdit4("Pick Color", (float*)&origColor)) {
		meshes[idx]->setColors(origColor);
	}

	// translate
	if (ImGui::Button("Translate : +x")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addTranslate(glm::vec3(1, 0, 0));
    }
	ImGui::SameLine();
	if (ImGui::Button("Translate : -x")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addTranslate(glm::vec3(-1, 0, 0));
    }
	ImGui::Spacing();
	if (ImGui::Button("Translate : +y")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addTranslate(glm::vec3(0, 1, 0));
    }
	ImGui::SameLine();
	if (ImGui::Button("Translate : -y")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addTranslate(glm::vec3(0, -1, 0));
    }
	ImGui::Spacing();
	if (ImGui::Button("Translate : +z")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addTranslate(glm::vec3(0, 0, 1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Translate : -z")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addTranslate(glm::vec3(0, 0, -1));
    }

	// rotate
	ImGui::Spacing();
	if (ImGui::Button("Rotate : +x")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addRotate(glm::vec3(1, 0, 0), 10);
    }
	ImGui::SameLine();
	if (ImGui::Button("Rotate : -x")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addRotate(glm::vec3(1, 0, 0), -10);
    }
	ImGui::Spacing();
	if (ImGui::Button("Rotate : +y")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addRotate(glm::vec3(0, 1, 0), 10);
    }
	ImGui::SameLine();
	if (ImGui::Button("Rotate : -y")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addRotate(glm::vec3(0, 1, 0), -10);
    }
	ImGui::Spacing();
	if (ImGui::Button("Rotate : +z")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addRotate(glm::vec3(0, 0, 1), 10);
    }
	ImGui::SameLine();
	if (ImGui::Button("Rotate : -z")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addRotate(glm::vec3(0, 0, 1), -10);
    }

	// scale
	ImGui::Spacing();
	if (ImGui::Button("Scale : +x")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addScale(glm::vec3(1.1, 1, 1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Scale : -x")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addScale(glm::vec3(0.9, 1, 1));
    }
	ImGui::Spacing();
	if (ImGui::Button("Scale : +y")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addScale(glm::vec3(1, 1.1, 1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Scale : -y")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addScale(glm::vec3(1, 0.9, 1));
    }
	ImGui::Spacing();
	if (ImGui::Button("Scale : +z")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addScale(glm::vec3(1, 1, 1.1));
    }
	ImGui::SameLine();
	if (ImGui::Button("Scale : -z")) {
        // 값이 변경될 때 수행할 작업
        meshes[idx]->addScale(glm::vec3(1, 1, 0.9));
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
	CGL::Device& device = CGL::Device::getInstance();
	device.init();
	device.createWindow("Renderer", WIDTH, HEIGHT);
	glfwSetWindowCloseCallback(device.window, windowCloseCallback);
	device.setup();

	CGL::Scene scene;

	CGL::ImguiDevice imguiDevice(device);

	int width, height;
	glfwGetWindowSize(device.window, &width, &height);

	std::vector<CGL::Mesh*> meshes;
	CGL::Mesh* cor = new CGL::Mesh();
	CGL::Mesh* openBox = getOpenBoxMesh();
	CGL::Mesh* defaultBox = getBoxMesh();
	CGL::Mesh* floor = getBoxMesh();
	CGL::Light* spotLight = new CGL::Light();
	CGL::Light* directionLight = new CGL::Light();
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
			spotLight->setAmbientcolor(glm::vec3(0.3, 0.3, 0.3));
			spotLight->setDiffusecolor(glm::vec3(0.5, 0.5, 0.5));
			spotLight->setSpecularcolor(glm::vec3(1, 1, 1));
			spotLight->setIntensity(0.5);
			spotLight->setConstantAttenuation(0.01);
			spotLight->setLinearAttenuation(0.01);
			spotLight->setQuadraticAttenuation(0.01);
			float temp = 2.f;
			spotLight->setPosition(glm::vec3(0.6 + temp, 2.1 + temp, 0.6 + temp));
			spotLight->setEmitDirection(glm::vec3(-1, -1, -1));
			spotLight->setInnerCutoff(glm::radians(15.f));
			spotLight->setOuterCutoff(glm::radians(30.f));

			CGL::Mesh* box = getBoxMesh();
			box->setScale(glm::vec3(0.1, 0.1, 0.1));
			spotLight->addChild(box);
		}
		
		{
			directionLight->setLightType(CGL::LIGHT_DIRECTIONAL);
			directionLight->setAmbientStrength(1);
			directionLight->setDiffuseStrength(1);
			directionLight->setSpecularStrength(1);
			directionLight->setAmbientcolor(glm::vec3(0.3, 0.3, 0.1));
			directionLight->setDiffusecolor(glm::vec3(0.5, 0.5, 0.3));
			directionLight->setSpecularcolor(glm::vec3(1, 1, 0.8));
			directionLight->setIntensity(0.5);
			directionLight->setConstantAttenuation(0.01);
			directionLight->setLinearAttenuation(0.01);
			directionLight->setQuadraticAttenuation(0.01);
			directionLight->setPosition(glm::vec3(-50, -50, -50));
			directionLight->setEmitDirection(glm::vec3(-1, -1, -1));
			directionLight->setInnerCutoff(glm::radians(20.f));
			directionLight->setOuterCutoff(glm::radians(45.f));
		}
	
		{
			CGL::Light* cameraLight = new CGL::Light();
			cameraLight->setLightType(CGL::LIGHT_SPOT);
			cameraLight->setAmbientStrength(1);
			cameraLight->setDiffuseStrength(1);
			cameraLight->setSpecularStrength(1);
			cameraLight->setAmbientcolor(glm::vec3(0.3, 0.3, 0.3));
			cameraLight->setDiffusecolor(glm::vec3(0.5, 0.5, 0.5));
			cameraLight->setSpecularcolor(glm::vec3(1, 1, 1));
			cameraLight->setIntensity(0.5);
			cameraLight->setConstantAttenuation(0.01);
			cameraLight->setLinearAttenuation(0.01);
			cameraLight->setQuadraticAttenuation(0.01);
			cameraLight->setPosition(glm::vec3(0, -1, 0));
			cameraLight->setEmitDirection(glm::vec3(0, 0, -1));
			cameraLight->setInnerCutoff(glm::radians(5.f));
			cameraLight->setOuterCutoff(glm::radians(10.f));

			// camera->addChild(cameraLight);

			camera->setViewPosition(glm::vec3(0.5, 2.5, 0.5));
			camera->setViewRotate(glm::vec3(-1, -1, -1));
		}
	
		{
			defaultBox->setTranslate(glm::vec3(0, 2, 0));
			floor->setScale(glm::vec3(50, 1, 50));
		}
	}

	// scene.addObject(cor);
	// scene.addObject(openBox);
	scene.addObject(defaultBox);
	scene.addObject(floor);
	// scene.addObject(spotLight);
	scene.addObject(directionLight);
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
		// spotLight->addRotate(glm::vec3(0, 1, 0), glm::radians(1.f));
		// loop begin process
		device.loopBeginProcess();

		if (moveMode) {
			processMainRenderWork(scene, before, prevXPos, prevYPos);
		}

		// render
		device.render(&scene);

        // GUI 구성
		if (!moveMode) {
			imguiDevice.loopBeginProcess();
			setImGuiWindow(scene, meshes);
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

	delete cor;
	delete openBox;
	delete defaultBox;
	delete floor;
	delete spotLight;
	delete directionLight;
	delete camera;

	for (int i = 0; i < meshes.size(); i++)
		delete meshes[i];
}