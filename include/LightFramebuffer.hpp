#ifndef LIGHTFRAMEBUFFER_HPP
#define LIGHTFRAMEBUFFER_HPP

#include <iFramebuffer.hpp>

#include <glad/glad.h>

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