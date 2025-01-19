#include <FramebufferManager.hpp>

void CGL::FramebufferManager::addFramebuffer(std::string const &name, GLsizei width, GLsizei height) {
	Framebuffer tmp(width, height, false, 0);
	this->framebuffers.insert(std::make_pair(name, tmp));
}

CGL::IFramebuffer* CGL::FramebufferManager::findFramebuffer(std::string const &name) {
	if (this->framebuffers.find(name) != this->framebuffers.end())
		return nullptr;
	return &(this->framebuffers.find(name)->second);
}

void CGL::FramebufferManager::addHDRFramebuffer(std::string const &name, GLsizei width, GLsizei height) {
	Framebuffer tmp(width, height, false, 16);
	this->framebuffers.insert(std::make_pair(name, tmp));
}
void CGL::FramebufferManager::addLightFramebuffer(std::string const &name, GLsizei width, GLsizei height) {
	LightFramebuffer tmp(width, height);
	this->framebuffers.insert(std::make_pair(name, tmp));
}
void CGL::FramebufferManager::addPointLightFramebuffer(std::string const &name, GLsizei width, GLsizei height) {
	PointLightFramebuffer tmp(width, height);
	this->framebuffers.insert(std::make_pair(name, tmp));
}

void CGL::FramebufferManager::deleteFramebuffer(std::string const &name) {
	this->framebuffers.erase(name);
}

void CGL::FramebufferManager::useFramebuffer(std::string const &name) {
	this->framebuffers.find(name)->second.use();
}

void CGL::FramebufferManager::useDefaultFramebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint CGL::FramebufferManager::getTexture(std::string const &name) {
	return this->framebuffers.find(name)->second.getTexture();
}