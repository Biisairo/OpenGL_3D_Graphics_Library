#ifndef IRESOURCEID
#define IRESOURCEID

#include <queue>

class IResourceID {
	private:
		static std::queue<unsigned int> IDPool;
		static unsigned int nextID;
		unsigned int ID;
	
	public:
		IResourceID();
		virtual ~IResourceID();
		IResourceID(const IResourceID&);
    	IResourceID& operator=(const IResourceID&);

		unsigned int getID();

	private:
		unsigned int setID();
};

#endif