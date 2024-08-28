#include "main.hpp"
#include "ProgramManager.hpp"

int main(int ac, char** av) {
	ProgramManager programManager;

	programManager.loadShader(VERTEX_SHADER, "normal", "./src/shader/normal.vs");
}