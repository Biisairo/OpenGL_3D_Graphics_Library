#ifndef IRESOURCEID
#define IRESOURCEID

#include "pch.hpp"
#include <queue>

class IResourceID {
	private:
		static std::queue<uint> IDPool;
		static uint nextID;
		uint ID;
	
	public:
		IResourceID();
		virtual ~IResourceID();
		IResourceID(const IResourceID&);
    	IResourceID& operator=(const IResourceID&);

		uint getID();

	private:
		uint setID();
};

#endif