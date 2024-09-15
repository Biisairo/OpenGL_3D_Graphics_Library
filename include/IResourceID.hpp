#ifndef IRESOURCEID_HPP
#define IRESOURCEID_HPP

#include <queue>

namespace CGL {

	class IResourceID {
		private:
			static std::queue<unsigned int> IDPool;
			static unsigned int nextID;
			unsigned int ID;
		
		public:
			IResourceID();
			virtual ~IResourceID();
			IResourceID(const IResourceID& other);
			IResourceID& operator=(const IResourceID& other);

			unsigned int getID();

		private:
			unsigned int setID();
	};

} // namespace CGL

#endif