# cmake version
cmake_minimum_required(VERSION 3.27)

# set variable
set(PROJECT_NAME opengl_engine)
set(CMAKE_CXX_STANDARD 11)

# set project
project(
	${PROJECT_NAME}
	LANGUAGES CXX
)

# set source code
set(SOURCE_CODE ${SOURCE_CODE}
    ./src/main.cpp 

    ./src/ImguiDevice.cpp 

    ./src/Device.cpp 
    ./src/Scene.cpp

    ./src/IResourceID.cpp 

    ./src/ICamera.cpp 
    ./src/IFramebuffer.cpp 
    ./src/IObject3D.cpp 

    ./src/FramebufferManager.cpp 
    ./src/Framebuffer.cpp 
    ./src/LightFramebuffer.cpp 
    ./src/PointLightFramebuffer.cpp 

    ./src/Light.cpp 
    ./src/Material.cpp 
    ./src/Mesh.cpp 
    ./src/ObjectCamera.cpp 
    ./src/PlayerCamera.cpp 
)

# start build
add_executable(${PROJECT_NAME} ${SOURCE_CODE})

# dependency import
include(Dependency.cmake)

# include path
target_include_directories(${PROJECT_NAME} PUBLIC ./include)

# include, link for dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw glad glm imgui
    "-framework CoreVideo"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework Carbon"
    "-framework QuartzCore"
)