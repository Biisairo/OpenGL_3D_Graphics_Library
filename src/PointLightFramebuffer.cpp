#include <PointLightFramebuffer.hpp>

CGL::PointLightFramebuffer::PointLightFramebuffer(GLsizei width, GLsizei height) {
	glGenFramebuffers(1, &this->framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
	for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->texture, 0);
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

// void CGL::PointLightFramebuffer::setError() {
// 	glDeleteFramebuffers(1, &this->framebuffer);
// 	glDeleteTextures(1, &this->texture);
// 	glDeleteRenderbuffers(1, &this->renderbuffer);
// 	this->framebuffer = 0;
// 	this->texture = 0;
// 	this->renderbuffer = 0;
// }

// void CGL::PointLightFramebuffer::use() {
// 	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
// }

// GLuint CGL::PointLightFramebuffer::getTexture() {
// 	return this->texture;
// }

// void CGL::PointLightFramebuffer::render(GLenum face) {
//     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, face, this->texture, 0);
// }