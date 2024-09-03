#include "IResourceID.hpp"

std::queue<uint> IResourceID::IDPool;
uint IResourceID::nextID = 0;

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

uint IResourceID::getID() {
	return this->ID;
}

uint IResourceID::setID() {
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