#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <algorithm>

#include "IObject3D.hpp"

namespace CGL {

	class Scene {
		private:
			CGL::IObject3D* root;
			objectID mainCameraID;

		public:
			Scene();
			~Scene();
			Scene(const Scene& other) = delete;
			Scene& operator=(const Scene& other) = delete;

			void addObject(IObject3D* object);
			void removeObject(objectID ID);
			void setMainCamera(objectID mainCameraID);

		private:
	};

} // namespace CGL

#endif