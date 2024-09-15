#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include "Extern/OpenGLHeader.hpp"

namespace CGL {

	class Texture {
		private:
			GLuint textureID;

		public:
			Texture();
			~Texture();
			Texture(const Texture& other) = delete;
			Texture& operator=(const Texture& other) = delete;

			void loadTexture(std::string const &imagepath, bool Alpha, bool gamma);

		private:
	};

} // namespace CGL

#endif