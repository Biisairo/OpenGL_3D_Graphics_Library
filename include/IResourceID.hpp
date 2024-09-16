#ifndef IRESOURCEID_HPP
#define IRESOURCEID_HPP

#include <queue>

using objectID = unsigned int;

namespace CGL {

	class IResourceID {
		private:
			static std::queue<objectID> IDPool;
			static objectID nextID;
			objectID ID;
		
		public:
			IResourceID();
			virtual ~IResourceID();
			IResourceID(const IResourceID& other);
			IResourceID& operator=(const IResourceID& other);

			objectID getID();

		private:
			objectID setID();
	};

} // namespace CGL

#endif