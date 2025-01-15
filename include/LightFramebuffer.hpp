#ifndef LIGHTFRAMEBUFFER_HPP
#define LIGHTFRAMEBUFFER_HPP

#include "Extern/OpenGLHeader.hpp"

#include <iFramebuffer.hpp>

#include <iostream>

class LightFramebuffer : public iFramebuffer {

	private:

		// GLuint framebuffer;
		// GLuint texture;
		// GLuint renderbuffer;

		// void setError();

	public:

		LightFramebuffer() = delete;
		LightFramebuffer(GLsizei witdh, GLsizei height);
		// ~Framebuffer();
		// Framebuffer(const Framebuffer& other);
		// Framebuffer& operator=(const Framebuffer& other);

		// void use();
		// GLuint getTexture();

};

#endif