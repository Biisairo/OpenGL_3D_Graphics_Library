#include "Material.hpp"

CGL::Material::Material() {
	// this->diffuseMapID = 0;
	// this->specularMapID = 0;
	// this->normalMapID = 0;
	// this->heightMapID = 0;
}

CGL::Material::~Material() {

}

CGL::Material::Material(const Material& other) {
	this->ambient = other.ambient;
	this->diffuse = other.diffuse;
	this->specular = other.specular;
	this->shininess = other.shininess;

	// this->diffuseMapID = other.diffuseMapID;
	// this->specularMapID = other.specularMapID;
	// this->normalMapID = other.normalMapID;
	// this->heightMapID = other.heightMapID;
}

CGL::Material& CGL::Material::operator=(const Material& other) {
	if (this != &other) {
		this->ambient = other.ambient;
		this->diffuse = other.diffuse;
		this->specular = other.specular;
		this->shininess = other.shininess;
		
	// 	this->diffuseMapID = other.diffuseMapID;
	// 	this->specularMapID = other.specularMapID;
	// 	this->normalMapID = other.normalMapID;
	// 	this->heightMapID = other.heightMapID;
	}

	return *this;
}


// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

// getter
glm::vec3 CGL::Material::getAmbient() {
	return this->ambient;
}

glm::vec3 CGL::Material::getDiffuse() {
	return this->diffuse;
}

glm::vec3 CGL::Material::getSpecular() {
	return this->specular;
}

float CGL::Material::getShininess() {
	return this->shininess;
}

// objectID CGL::Material::getDiffuseMap() {
// 	return this->diffuseMapID;
// }

// objectID CGL::Material::getSpecularMap() {
// 	return this->specularMapID;
// }

// objectID CGL::Material::getNormalMap() {
// 	return this->normalMapID;
// }

// objectID CGL::Material::getHeightMap() {
// 	return this->heightMapID;
// }


// setter
void CGL::Material::setAmbient(glm::vec3 ambient) {
	this->ambient = ambient;
}

void CGL::Material::setDiffuse(glm::vec3 diffuse) {
	this->diffuse = diffuse;
}

void CGL::Material::setSpecular(glm::vec3 specular) {
	this->specular = specular;
}

void CGL::Material::setShininess(float shininess) {
	this->shininess = shininess;
}

// void CGL::Material::setDiffuseMap(objectID ID) {
// 	this->diffuseMapID = ID;
// }

// void CGL::Material::setSpecularMap(objectID ID) {
// 	this->specularMapID = ID;
// }

// void CGL::Material::setNormalMap(objectID ID) {
// 	this->normalMapID = ID;
// }

// void CGL::Material::setHeightMap(objectID ID) {
// 	this->heightMapID = ID;
// }

