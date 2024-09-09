#include <UniformBlockManager.hpp>

UniformBlockManager::UniformBlockManager() {}

UniformBlockManager::~UniformBlockManager() {}

void UniformBlockManager::addUniformBlock(std::string const &uniformBlockName, std::vector<GLuint> &programs) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		UniformBlock &ub = this->uniformBlocks[uniformBlockName];

		for (int i = 0; i < programs.size(); i++) {
			if (ub.uniformBlockIndex.count(programs[i]))
				continue;

			GLuint id = glGetUniformBlockIndex(programs[i], uniformBlockName.c_str());
			ub.uniformBlockIndex.insert(std::make_pair(programs[i], id));
			glUniformBlockBinding(programs[i], id, 0);
		}
	} else {
		UniformBlock ub;

		for (int i = 0; i < programs.size(); i++) {
			GLuint id = glGetUniformBlockIndex(programs[i], uniformBlockName.c_str());
			ub.uniformBlockIndex.insert(std::make_pair(programs[i], id));
			glUniformBlockBinding(programs[i], id, 0);
		}
		glGenBuffers(1, &ub.uniformBlockBuffer);

		this->uniformBlocks.insert(std::make_pair(uniformBlockName, ub));
	}
}

GLuint UniformBlockManager::getUniformBlockBuffer(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName))
		return this->uniformBlocks[uniformBlockName].uniformBlockBuffer;
	return 0;
}

void UniformBlockManager::deleteUniformBlock(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		glDeleteBuffers(1, &this->uniformBlocks[uniformBlockName].uniformBlockBuffer);
	}
}

void UniformBlockManager::useUniformBlock(std::string const &uniformBlockName) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		glBindBuffer(GL_UNIFORM_BUFFER, this->uniformBlocks[uniformBlockName].uniformBlockBuffer);
	}
}

void UniformBlockManager::unuseUniformBlock() {
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBlockManager::setUniformBufferData(std::string const &uniformBlockName, size_t size, void* data) {
	if (this->uniformBlocks.count(uniformBlockName)) {
		UniformBlock &ub = this->uniformBlocks[uniformBlockName];

		glBindBuffer(GL_UNIFORM_BUFFER, ub.uniformBlockBuffer);

		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, ub.uniformBlockBuffer, 0, size);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}