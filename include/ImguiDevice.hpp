#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Device.hpp"

namespace CGL {

	class ImguiDevice {
		private:

		public:
			ImguiDevice(Device& device);
			~ImguiDevice();
			ImguiDevice(const ImguiDevice& other) = delete;
			ImguiDevice& operator=(const ImguiDevice& other) = delete;

			void loopBeginProcess();
			void loopEndProcess();

		private:
	};

}