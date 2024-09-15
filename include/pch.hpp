#ifndef PCH_HPP
#define PCH_HPP

#define SHADER_PATH "./src/shader/"

#define COMMON_SHADER_VERT "vs/CameraNormal.vert"
#define COMMON_SHADER_FRAG "fs/CameraNormal.frag"

#define GLFW_USE 1
#define GLAD_USE 1
#define GLM_USE 1
#define STB_IMAGE_USE 0
#define ASSIMP_USE 0
#define SPDLOG_USE 0
#define IMGUI_USE 0

// opengl
#if GLFW_USE && GLAD_USE
	#include "Extern/OpenGLHeader.hpp"
#endif

// glm
#if GLM_USE
	#include "Extern/GLMHeader.hpp"
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