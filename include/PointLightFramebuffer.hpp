#ifndef POINTLIGHTFRAMEBUFFER_HPP
#define POINTLIGHTFRAMEBUFFER_HPP

#include <IFramebuffer.hpp>

#include <glad/glad.h>

#include <iostream>

namespace CGL {

	class PointLightFramebuffer : public IFramebuffer {

		private:

			// GLuint framebuffer;
			// GLuint texture;
			// GLuint renderbuffer;

			// void setError();

		public:

			PointLightFramebuffer() = delete;
			PointLightFramebuffer(GLsizei witdh, GLsizei height);
			// ~Framebuffer();
			// Framebuffer(const Framebuffer& other);
			// Framebuffer& operator=(const Framebuffer& other);

			// void use();
			// GLuint getTexture();
			// void render(GLenum face);
	};
}

#endif