#ifndef PCH_HPP
#define PCH_HPP

// std
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

#define GLFW_USE 1
#define GLAD_USE 1
#define GLM_USE 1
#define STB_IMAGE_USE 0
#define ASSIMP_USE 0
#define SPDLOG_USE 0
#define IMGUI_USE 0

// opengl
#if GLFW_USE && GLAD_USE
	#define GL_SILENCE_DEPRECATION
	#define GLFW_INCLUDE_NONE
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
#endif

// glm
#if GLM_USE
	#define GLM_ENABLE_EXPERIMENTAL
	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
	#include <glm/gtx/transform.hpp>
#endif

// stb
#if STB_IMAGE_USE
	#include <stb/stb_image.h>
#endif

// assimp
#if ASSIMP_USE
	#include <assimp/Importer.hpp>
	#include <assimp/scene.h>
	#include <assimp/postprocess.h>
#endif

// spdlog
#if SPDLOG_USE
	#include <spdlog/spdlog.h>
#endif

// imgui
#if IMGUI_USE
	#include <imgui/imgui.h>
	#include <imgui/imgui_impl_glfw.h>
	#include <imgui/imgui_impl_opengl3.h>
#endif

#endif