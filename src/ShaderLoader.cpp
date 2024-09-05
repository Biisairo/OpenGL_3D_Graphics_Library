#include "ShaderLoader.hpp"

std::string loadShaderCode(std::string const &fileName) {
	std::string filePath = SHADER_PATH + fileName;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderCode;
    std::string line;

    while (std::getline(file, line)) {
        if (line.find("#include ") != std::string::npos) {
            size_t firstQuote = line.find_first_of("<");
            size_t lastQuote = line.find_last_of(">");
            if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote > firstQuote) {
                std::string includeFile = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

                std::string includeCode = loadShaderCode(includeFile);
                shaderCode << includeCode << std::endl;
            }
        } else {
            shaderCode << line << std::endl;
        }
    }

    return shaderCode.str();
}
