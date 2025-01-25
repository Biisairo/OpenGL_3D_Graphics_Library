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

CGL::IObject3D* getOpenBoxMesh() {
	CGL::IObject3D* box = new CGL::IObject3D();

	CGL::Mesh* bottom = getBoxMesh();
	bottom->setTranslate(glm::vec3(0, -5, 0));
	bottom->setScale(glm::vec3(4.5, 0.5, 4.5));
	bottom->setColors(glm::vec4(0.8, 0.7, 0.5, 1));
	
	CGL::Mesh* top = getBoxMesh();
	top->setTranslate(glm::vec3(0, 5, 0));
	top->setScale(glm::vec3(4.5, 0.5, 4.5));
	top->setColors(glm::vec4(0.8, 0.7, 0.5, 1));
	
	CGL::Mesh* back = getBoxMesh();
	back->setTranslate(glm::vec3(0, 0, 5));
	back->setScale(glm::vec3(4.5, 4.5, 0.5));
	back->setColors(glm::vec4(0.8, 0.7, 0.5, 1));
	
	CGL::Mesh* right = getBoxMesh();
	right->setTranslate(glm::vec3(-5, 0, 0));
	right->setScale(glm::vec3(0.5, 4.5, 4.5));
	right->setColors(glm::vec4(0.2, 0.4, 0.1, 1));
	
	CGL::Mesh* left = getBoxMesh();
	left->setTranslate(glm::vec3(5, 0, 0));
	left->setScale(glm::vec3(0.5, 4.5, 4.5));
	left->setColors(glm::vec4(0.5, 0.2, 0.1, 1));

	box->addChild(bottom);
	box->addChild(top);
	box->addChild(back);
	box->addChild(right);
	box->addChild(left);

	return box;
}

void setImGuiWindow(CGL::Scene& scene, std::vector<CGL::Mesh*>& meshes) {
	static int idx = -1;

	static bool isHDR = false;
	static bool isShadow = false;
	static bool isNormal = false;
	static bool drawLine = false;

	CGL::Device& device = CGL::Device::getInstance();

	ImGui::SetNextWindowSize(ImVec2(300, 360));
	ImGui::Begin("Mesh Controller", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	ImGui::BeginGroup();
	if (ImGui::Checkbox("HDR", &isHDR)) {
        device.useHDR(isHDR);
    }
	ImGui::SameLine();
	if (ImGui::Checkbox("Shadow", &isShadow)) {
        device.renderShadow(isShadow);
    }
	ImGui::SameLine();
	if (ImGui::Checkbox("Normal", &isNormal)) {
        device.renderNormal(isNormal);
    }

	ImGui::EndGroup();

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

	if (idx != -1) {
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
	}

	ImGui::End();
	
	ImGuiStyle& style = ImGui::GetStyle();
    ImVec2 originalWindowPadding = style.WindowPadding;
	style.WindowPadding = ImVec2(0, 0);

	int windowWidth, windowHeight;
	glfwGetWindowSize(device.window, &windowWidth, &windowHeight);
    ImGui::SetNextWindowSize(ImVec2(200, 100));
	ImGui::SetNextWindowPos(ImVec2((windowWidth - 200) / 2, (windowHeight - 100) / 2));

	ImGui::Begin("test", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.3f));
	if (ImGui::Button("END PROGRAM", ImGui::GetContentRegionAvail())) {
		glfwSetWindowShouldClose(device.window, GLFW_TRUE);
    }
	ImGui::PopStyleColor(3);

	ImGui::End();

	style.WindowPadding = originalWindowPadding;
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
	CGL::IObject3D* openBox = getOpenBoxMesh();
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
			spotLight->setPosition(glm::vec3(0, 4, 0));
			spotLight->setEmitDirection(glm::vec3(0, -1, 0));
			spotLight->setInnerCutoff(glm::radians(100.f));
			spotLight->setOuterCutoff(glm::radians(120.f));
		}
		
		{
			directionLight->setLightType(CGL::LIGHT_DIRECTIONAL);
			directionLight->setAmbientStrength(1);
			directionLight->setDiffuseStrength(1);
			directionLight->setSpecularStrength(1);
			directionLight->setAmbientcolor(glm::vec3(0.3, 0.3, 0.3));
			directionLight->setDiffusecolor(glm::vec3(0.5, 0.5, 0.5));
			directionLight->setSpecularcolor(glm::vec3(1, 1, 1));
			directionLight->setIntensity(0.5);
			directionLight->setConstantAttenuation(0.01);
			directionLight->setLinearAttenuation(0.01);
			directionLight->setQuadraticAttenuation(0.01);
			directionLight->setPosition(glm::vec3(4, 4, 4));
			directionLight->setEmitDirection(glm::vec3(-1, -1, -1));
			directionLight->setInnerCutoff(glm::radians(20.f));
			directionLight->setOuterCutoff(glm::radians(45.f));
		}
	}

	scene.addObject(cor);
	scene.addObject(openBox);
	scene.addObject(spotLight);
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
	delete spotLight;
	delete directionLight;
	delete camera;

	for (int i = 0; i < meshes.size(); i++)
		delete meshes[i];
}