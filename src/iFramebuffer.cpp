#include <IFramebuffer.hpp>

// IFramebuffer::IFramebuffer() {}

// IFramebuffer::~IFramebuffer() {}

// IFramebuffer::IFramebuffer(const IFramebuffer& other) {}

// IFramebuffer& IFramebuffer::operator=(const IFramebuffer& other) {
// 	if (this == &other)
// 		return *this;
// 	return *this;
// }

void IFramebuffer::setError() {
	glDeleteFramebuffers(1, &this->framebuffer);
	glDeleteTextures(1, &this->texture);
	glDeleteRenderbuffers(1, &this->renderbuffer);
	this->framebuffer = 0;
	this->texture = 0;
	this->renderbuffer = 0;
}

void IFramebuffer::use() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
}

GLuint IFramebuffer::getTexture() {
	return this->texture;
}