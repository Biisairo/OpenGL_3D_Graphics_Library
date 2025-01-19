#ifndef IFRAMEBUFFER_HPP
#define IFRAMEBUFFER_HPP

#include "Extern/OpenGLHeader.hpp"

namespace CGL {

	class IFramebuffer{

		protected:

			GLuint framebuffer;
			GLuint texture;
			GLuint renderbuffer;

			void setError();

		public:
			void use();
			GLuint getTexture();

	};
}

#endif