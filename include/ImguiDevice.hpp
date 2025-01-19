#include "Extern/ImguiHeader.hpp"

#include "Device.hpp"

namespace CGL {

	class ImguiDevice {
		private:

		public:
			ImguiDevice(Device& device);
			~ImguiDevice();
			ImguiDevice(const ImguiDevice& other) = delete;
			ImguiDevice& operator=(const ImguiDevice& other) = delete;

			ImGuiIO& getImGuiIO();

			void loopBeginProcess();
			void loopEndProcess();

		private:
	};

}