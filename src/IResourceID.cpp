#include "IResourceID.hpp"

// ID 0 for None
std::queue<unsigned int> CGL::IResourceID::IDPool;
unsigned int CGL::IResourceID::nextID = 1;

CGL::IResourceID::IResourceID() {
	this->setID();
}

CGL::IResourceID::~IResourceID() {
	this->IDPool.push(this->ID);
}

CGL::IResourceID::IResourceID(const IResourceID& other) {
	this->setID();
}
CGL::IResourceID& CGL::IResourceID::operator=(const IResourceID& other) {
	this->setID();
	return *this;
}


// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int CGL::IResourceID::getID() {
	return this->ID;
}


// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int CGL::IResourceID::setID() {
	if (this->IDPool.size() > 0) {
		this->ID = this->IDPool.front();
		this->IDPool.pop();
	}
	else {
		this->ID = this->nextID;
		this->nextID++;
	}

	return this->ID;
}