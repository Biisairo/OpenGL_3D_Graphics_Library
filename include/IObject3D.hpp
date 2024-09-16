#ifndef IOBJECT3D_HPP
#define IOBJECT3D_HPP

#include <vector>

#include "IResourceID.hpp"
#include "Extern/GLMHeader.hpp"

namespace CGL {

	enum ObjectType {
		OBJECT_NONE,
		OBJECT_CAMERA,
		OBJECT_MESH,
		OBJECT_LIGHT
	};

	class IObject3D : public IResourceID {
		private:
			IObject3D* parent;
			std::vector<IObject3D*> children;

			glm::mat4 model;
			glm::mat4 scale;
			glm::mat4 rotate;
			glm::mat4 translate;

		public:
			IObject3D();
			~IObject3D();
			IObject3D(const IObject3D& other);
			IObject3D& operator=(const IObject3D& other);

			void setParent(IObject3D *parent);
			IObject3D* getParent();
			void addChild(IObject3D *child);
			IObject3D* findChild(objectID ID);
			IObject3D* removeChild(objectID ID);
			std::vector<IObject3D*>& getChildren();

			void initModel();

			void setScale(glm::vec3 scale);
			void addScale(glm::vec3 scale);
			void setRotate(glm::vec3 axis, float angle);
			void addRotate(glm::vec3 axis, float angle);
			void setTranslate(glm::vec3 translate);
			void addTranslate(glm::vec3 translate);

			glm::mat4& getModel();
			
			virtual ObjectType getObjectType();
		
		private:
	};

} // namespace CGL

#endif