#ifndef UNIFORMBLOCKMANAGER_HPP
#define UNIFORMBLOCKMANAGER_HPP

#include "pch.hpp"
#include "CommonEnum.hpp"

struct UniformBlock {
	GLuint uniformBlockBuffer;
	std::unordered_map<GLuint, GLuint> uniformBlockIndex;
};

class UniformBlockManager{

	private:
		std::unordered_map<std::string, UniformBlock> uniformBlocks;

	public:
		UniformBlockManager();
		~UniformBlockManager();

		void addUniformBlock(std::string const &uniformBlockName, std::vector<GLuint> &programs);
		GLuint getUniformBlockBuffer(std::string const &uniformBlockName);
		void deleteUniformBlock(std::string const &uniformBlockName);
		void useUniformBlock(std::string const &uniformBlockName);
		void unuseUniformBlock();

		void setUniformBufferData(std::string const &uniformBlockName, size_t size, void* data);

};

#endif