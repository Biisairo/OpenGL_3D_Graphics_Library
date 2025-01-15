#include <LightFramebuffer.hpp>

LightFramebuffer::LightFramebuffer(GLsizei width, GLsizei height) {
	glGenFramebuffers(1, &this->framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
				width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Framebuffer::~Framebuffer() {}

// Framebuffer::Framebuffer(const Framebuffer& other) {}

// Framebuffer& Framebuffer::operator=(const Framebuffer& other) {
// 	if (this == &other)
// 		return *this;
// 	return *this;
// }

// void LightFramebuffer::setError() {
// 	glDeleteFramebuffers(1, &this->framebuffer);
// 	glDeleteTextures(1, &this->texture);
// 	glDeleteRenderbuffers(1, &this->renderbuffer);
// 	this->framebuffer = 0;
// 	this->texture = 0;
// 	this->renderbuffer = 0;
// }

// void LightFramebuffer::use() {
// 	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
// }

// GLuint LightFramebuffer::getTexture() {
// 	return this->texture;
// }