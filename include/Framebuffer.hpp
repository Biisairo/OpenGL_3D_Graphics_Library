#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <IFramebuffer.hpp>

#include <glad/glad.h>

#include <iostream>

namespace CGL {

	class Framebuffer : public IFramebuffer {

		private:

			// GLuint framebuffer;
			// GLuint texture;
			// GLuint renderbuffer;

			// void setError();

		public:

			Framebuffer() = delete;
			Framebuffer(GLsizei width, GLsizei height, bool Alpha, int HDR);
			// ~Framebuffer();
			// Framebuffer(const Framebuffer& other);
			// Framebuffer& operator=(const Framebuffer& other);

			// void use();
			// GLuint getTexture();

	};
}

#endif