#ifndef FRAMEBUFFERMANAGER_HPP
#define FRAMEBUFFERMANAGER_HPP

#include <IFramebuffer.hpp>
#include <Framebuffer.hpp>
#include <LightFramebuffer.hpp>
#include <PointLightFramebuffer.hpp>

#include <map>
#include <string>

namespace CGL {

	class FramebufferManager{

		private:

			std::map<std::string, IFramebuffer> framebuffers;

		public:

			// FramebufferManager();
			// ~FramebufferManager();
			// FramebufferManager(const FramebufferManager& other);
			// FramebufferManager& operator=(const FramebufferManager& other);

			void addFramebuffer(std::string const &name, GLsizei width, GLsizei height);
			IFramebuffer* findFramebuffer(std::string const &name);
			void addHDRFramebuffer(std::string const &name, GLsizei width, GLsizei height);
			void addLightFramebuffer(std::string const &name, GLsizei width, GLsizei height);
			void addPointLightFramebuffer(std::string const &name, GLsizei width, GLsizei height);
			void deleteFramebuffer(std::string const &name);
			void useFramebuffer(std::string const &name);
			void defaultFramebuffer();
			GLuint getTexture(std::string const &name);

	};
}

#endif