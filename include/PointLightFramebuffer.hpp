#ifndef POINTLIGHTFRAMEBUFFER_HPP
#define POINTLIGHTFRAMEBUFFER_HPP

#include <IFramebuffer.hpp>

#include <glad/glad.h>

#include <iostream>

namespace CGL {

	class PointLightFramebuffer : public IFramebuffer {
		public:

			PointLightFramebuffer() = delete;
			PointLightFramebuffer(GLsizei witdh, GLsizei height);
	};
}

#endif