#include "IResourceID.hpp"

std::queue<unsigned int> IResourceID::IDPool;
unsigned int IResourceID::nextID = 0;

IResourceID::IResourceID() {
	this->setID();
}

IResourceID::~IResourceID() {
	this->IDPool.push(this->ID);
}

IResourceID::IResourceID(const IResourceID&) {
	this->setID();
}
IResourceID& IResourceID::operator=(const IResourceID&) {
	this->setID();
	return *this;
}

unsigned int IResourceID::getID() {
	return this->ID;
}

unsigned int IResourceID::setID() {
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