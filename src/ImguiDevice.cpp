#include "ImguiDevice.hpp"

CGL::ImguiDevice::ImguiDevice(CGL::Device& device) {
	// ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui 스타일 설정 (선택 사항)
    ImGui::StyleColorsDark();

    // ImGui 백엔드 초기화
    ImGui_ImplGlfw_InitForOpenGL(device.window, true);
    ImGui_ImplOpenGL3_Init("#version 410"); // OpenGL 버전 지정
}

CGL::ImguiDevice::~ImguiDevice() {
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImGuiIO& CGL::ImguiDevice::getImGuiIO() {
    return ImGui::GetIO();
}

void CGL::ImguiDevice::loopBeginProcess() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void CGL::ImguiDevice::loopEndProcess() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////