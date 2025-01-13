#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <algorithm>

#include "IObject3D.hpp"
#include "ICamera.hpp"

namespace CGL {

	class Scene {
		private:
			IObject3D root;
			ICamera* mainCamera;

		public:
			Scene();
			~Scene();
			Scene(const Scene& other) = delete;
			Scene& operator=(const Scene& other) = delete;

			IObject3D* getRoot();
			void addObject(IObject3D* object);
			IObject3D* findObject(objectID ID);
			IObject3D* removeObject(objectID ID);
			void setMainCamera(ICamera* mainCamera);
			ICamera* getMainCamera();

		private:
	};

} // namespace CGL

#endif