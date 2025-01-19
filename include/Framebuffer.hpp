#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <IFramebuffer.hpp>

#include <glad/glad.h>

#include <iostream>

namespace CGL {

	class Framebuffer : public IFramebuffer {
		public:
			Framebuffer() = delete;
			Framebuffer(GLsizei width, GLsizei height, bool Alpha, int HDR);
	};
}

#endif