#ifndef LIGHTFRAMEBUFFER_HPP
#define LIGHTFRAMEBUFFER_HPP

#include "Extern/OpenGLHeader.hpp"

#include <IFramebuffer.hpp>

#include <iostream>

namespace CGL {

	class LightFramebuffer : public IFramebuffer {
		public:

			LightFramebuffer() = delete;
			LightFramebuffer(GLsizei witdh, GLsizei height);
	};
}

#endif