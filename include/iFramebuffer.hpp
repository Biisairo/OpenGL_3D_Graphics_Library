#ifndef IFRAMEBUFFER_HPP
#define IFRAMEBUFFER_HPP

#include <glad/glad.h>

class iFramebuffer{

	protected:

		GLuint framebuffer;
		GLuint texture;
		GLuint renderbuffer;

		void setError();

	public:

		// iFramebuffer();
		// virtual ~iFramebuffer();
		// virtual iFramebuffer(const iFramebuffer& other);
		// virtual iFramebuffer& operator=(const iFramebuffer& other);
		void use();
		GLuint getTexture();

};

#endif