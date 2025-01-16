#include <IFramebuffer.hpp>

// CGL::IFramebuffer::CGL::IFramebuffer() {}

// CGL::IFramebuffer::~CGL::IFramebuffer() {}

// CGL::IFramebuffer::CGL::IFramebuffer(const CGL::IFramebuffer& other) {}

// CGL::IFramebuffer& CGL::IFramebuffer::operator=(const CGL::IFramebuffer& other) {
// 	if (this == &other)
// 		return *this;
// 	return *this;
// }

void CGL::IFramebuffer::setError() {
	glDeleteFramebuffers(1, &this->framebuffer);
	glDeleteTextures(1, &this->texture);
	glDeleteRenderbuffers(1, &this->renderbuffer);
	this->framebuffer = 0;
	this->texture = 0;
	this->renderbuffer = 0;
}

void CGL::IFramebuffer::use() {
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
}

GLuint CGL::IFramebuffer::getTexture() {
	return this->texture;
}