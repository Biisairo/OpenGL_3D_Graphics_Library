#include "Material.hpp"

CGL::Material::Material() {
}

CGL::Material::~Material() {

}

CGL::Material::Material(const Material& other) {
	this->ambientColor = other.ambientColor;
	this->diffuseColor = other.diffuseColor;
	this->specularColor = other.specularColor;
	this->alpha = other.alpha;
	this->shininess = other.shininess;
}

CGL::Material& CGL::Material::operator=(const Material& other) {
	if (this != &other) {
		this->ambientColor = other.ambientColor;
		this->diffuseColor = other.diffuseColor;
		this->specularColor = other.specularColor;
		this->alpha = other.alpha;
		this->shininess = other.shininess;
	}

	return *this;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Material::setAmbientColor(glm::vec3 ambientColor) {
	this->ambientColor = ambientColor;
}

void CGL::Material::setDiffuseColor(glm::vec3 diffuseColor) {
	this->diffuseColor = diffuseColor;
}

void CGL::Material::setSpecularColor(glm::vec3 specularColor) {
	this->specularColor = specularColor;
}

void CGL::Material::setAlpha(float alpha) {
	this->alpha = alpha;
}

void CGL::Material::setShininess(float shininess) {
	this->shininess = shininess;
}

glm::vec4 CGL::Material::getAmbientColor() {
	return glm::vec4(this->ambientColor, 1);
}

glm::vec4 CGL::Material::getDiffuseColor() {
	return glm::vec4(this->diffuseColor, 1);
}

glm::vec4 CGL::Material::getSpecularColor() {
	return glm::vec4(this->specularColor, 1);
}

float CGL::Material::getAlpha() {
	return this->alpha;
}

float CGL::Material::getShininess() {
	return this->shininess;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////