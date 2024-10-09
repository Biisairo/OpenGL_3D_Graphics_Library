#include "Light.hpp"

CGL::Light::Light() {
	;
}

CGL::Light::~Light() {
	;
}

CGL::Light::Light(const CGL::Light& other) : IObject3D(other) {
	this->lightType = other.lightType;
	this->ambientStrength = other.ambientStrength;
	this->diffuseStrength = other.diffuseStrength;
	this->specularStrength = other.specularStrength;
	this->ambientcolor = other.ambientcolor;
	this->diffusecolor = other.diffusecolor;
	this->specularcolor = other.specularcolor;
	this->intensity = other.intensity;
	this->constantAttenuation = other.constantAttenuation;
	this->linearAttenuation = other.linearAttenuation;
	this->quadraticAttenuation = other.quadraticAttenuation;
	this->position = other.position;
	this->emitDirection = other.emitDirection;
	this->innerCutoff = other.innerCutoff;
	this->outerCutoff = other.outerCutoff;
}

CGL::Light& CGL::Light::operator=(const CGL::Light& other) {
	if (this != &other) {
		CGL:IObject3D::operator=(other);

		this->lightType = other.lightType;
		this->ambientStrength = other.ambientStrength;
		this->diffuseStrength = other.diffuseStrength;
		this->specularStrength = other.specularStrength;
		this->ambientcolor = other.ambientcolor;
		this->diffusecolor = other.diffusecolor;
		this->specularcolor = other.specularcolor;
		this->intensity = other.intensity;
		this->constantAttenuation = other.constantAttenuation;
		this->linearAttenuation = other.linearAttenuation;
		this->quadraticAttenuation = other.quadraticAttenuation;
		this->position = other.position;
		this->emitDirection = other.emitDirection;
		this->innerCutoff = other.innerCutoff;
		this->outerCutoff = other.outerCutoff;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// public /////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CGL::Light::setLightType(CGL::LightType lightType) {
	this->lightType = lightType;
}
void CGL::Light::setAmbientStrength(float ambientStrength) {
	this->ambientStrength = ambientStrength;
}
void CGL::Light::setDiffuseStrength(float diffuseStrength) {
	this->diffuseStrength = diffuseStrength;
}
void CGL::Light::setSpecularStrength(float specularStrength) {
	this->specularStrength = specularStrength;
}
void CGL::Light::setAmbientcolor(glm::vec4 ambientcolor) {
	this->ambientcolor = ambientcolor;
}
void CGL::Light::setDiffusecolor(glm::vec4 diffusecolor) {
	this->diffusecolor = diffusecolor;
}
void CGL::Light::setSpecularcolor(glm::vec4 specularcolor) {
	this->specularcolor = specularcolor;
}
void CGL::Light::setIntensity(float intensity) {
	this->intensity = intensity;
}
void CGL::Light::setConstantAttenuation(float constantAttenuation) {
	this->constantAttenuation = constantAttenuation;
}
void CGL::Light::setLinearAttenuation(float linearAttenuation) {
	this->linearAttenuation = linearAttenuation;
}
void CGL::Light::setQuadraticAttenuation(float quadraticAttenuation) {
	this->quadraticAttenuation = quadraticAttenuation;
}
void CGL::Light::setPosition(glm::vec4 position) {
	this->position = position;

	this->setTranslate(position);
}
void CGL::Light::setEmitDirection(glm::vec4 emitDirection) {
	this->emitDirection = emitDirection;
}
void CGL::Light::setInnerCutoff(float innerCutoff) {
	this->innerCutoff = innerCutoff;
}
void CGL::Light::setOuterCutoff(float outerCutoff) {
	this->outerCutoff = outerCutoff;
}

CGL::LightType CGL::Light::getLightType() {
	return this->lightType;
}
float CGL::Light::getAmbientStrength() {
	return this->ambientStrength;
}
float CGL::Light::getDiffuseStrength() {
	return this->diffuseStrength;
}
float CGL::Light::getSpecularStrength() {
	return this->specularStrength;
}
glm::vec4 CGL::Light::getAmbientcolor() {
	return this->ambientcolor;
}
glm::vec4 CGL::Light::getDiffusecolor() {
	return this->diffusecolor;
}
glm::vec4 CGL::Light::getSpecularcolor() {
	return this->specularcolor;
}
float CGL::Light::getIntensity() {
	return this->intensity;
}
float CGL::Light::getConstantAttenuation() {
	return this->constantAttenuation;
}
float CGL::Light::getLinearAttenuation() {
	return this->linearAttenuation;
}
float CGL::Light::getQuadraticAttenuation() {
	return this->quadraticAttenuation;
}
glm::vec4 CGL::Light::getPosition() {
	return this->position;
}
glm::vec4 CGL::Light::getEmitDirection() {
	return this->emitDirection;
}
float CGL::Light::getInnerCutoff() {
	return this->innerCutoff;
}
float CGL::Light::getOuterCutoff() {
	return this->outerCutoff;
}

CGL::ObjectType CGL::Light::getObjectType() {
	return OBJECT_LIGHT;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private ////////////////////////////////////////////////////////////////////////////////////////////////////////////