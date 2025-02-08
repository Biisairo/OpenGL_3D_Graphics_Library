include(ExternalProject)

set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)

set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# glfw3
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "master"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    TEST_COMMAND ""
)

set(GLFW_INCLUDE ${DEP_INCLUDE_DIR}/GLFW)

add_library(glfw INTERFACE)
target_include_directories(glfw INTERFACE ${GLFW_INCLUDE})
target_link_libraries(glfw INTERFACE ${DEP_LIB_DIR}/libglfw3.a)

add_dependencies(glfw dep_glfw)

# glad
ExternalProject_Add(
    dep_glad
    GIT_REPOSITORY "https://github.com/Dav1dde/glad"
    GIT_TAG "v0.1.34"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLAD_INSTALL=ON
    TEST_COMMAND ""
)

set(GLAD_INCLUDE ${DEP_INCLUDE_DIR}/glad)

add_library(glad INTERFACE)
target_include_directories(glad INTERFACE ${GLAD_INCLUDE})
target_include_directories(glad INTERFACE ${DEP_INCLUDE_DIR})
target_link_libraries(glad INTERFACE ${DEP_LIB_DIR}/libglad.a)

add_dependencies(glad dep_glad)

# glm
ExternalProject_Add(
    dep_glm
    GIT_REPOSITORY "https://github.com/g-truc/glm"
    GIT_TAG "master"
    GIT_SHALLOW 1
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    TEST_COMMAND ""
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_BINARY_DIR}/dep_glm-prefix/src/dep_glm/glm
        ${DEP_INSTALL_DIR}/include/glm
)

set(GLM_INCLUDE ${DEP_INCLUDE_DIR}/glm)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE ${GLM_INCLUDE})

add_dependencies(glm dep_glm)

# imgui
include(FetchContent)
FetchContent_Declare(
        dep_imgui
        GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
        GIT_TAG "master"
)
FetchContent_MakeAvailable(dep_imgui)

set(IMGUI_INCLUDE ${DEP_INCLUDE_DIR}/imgui)
set(imgui_dir ${PROJECT_BINARY_DIR}/_deps/dep_imgui-src)

file(COPY ${imgui_dir}/imconfig.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/imgui.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/imgui_internal.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/imstb_rectpack.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/imstb_textedit.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/imstb_truetype.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/misc/cpp/imgui_stdlib.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/backends/imgui_impl_glfw.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/backends/imgui_impl_opengl3.h DESTINATION ${IMGUI_INCLUDE})
file(COPY ${imgui_dir}/backends/imgui_impl_opengl3_loader.h DESTINATION ${IMGUI_INCLUDE})

# add all source code
set(IMGUI_CODE
    ${imgui_dir}/imgui.cpp
    ${imgui_dir}/imgui_draw.cpp
    ${imgui_dir}/imgui_tables.cpp
    ${imgui_dir}/imgui_widgets.cpp
    ${imgui_dir}/misc/cpp/imgui_stdlib.cpp
    ${imgui_dir}/backends/imgui_impl_glfw.cpp
    ${imgui_dir}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_CODE})

set_target_properties(imgui PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${DEP_LIB_DIR})

target_include_directories(imgui PUBLIC ${IMGUI_INCLUDE})
target_include_directories(imgui PRIVATE ${DEP_INCLUDE_DIR})

add_dependencies(imgui dep_glfw)

# # stb_image
# if (${STB_IMAGE_USE})
#     ExternalProject_Add(
#         dep_stb
#         GIT_REPOSITORY "https://github.com/nothings/stb"
#         GIT_TAG "master"
#         GIT_SHALLOW 1
#         UPDATE_COMMAND ""
#         PATCH_COMMAND ""
#         CONFIGURE_COMMAND ""
#         BUILD_COMMAND ""
#         TEST_COMMAND ""
#         INSTALL_COMMAND
#             ${CMAKE_COMMAND} -E copy_directory
#                 ${PROJECT_BINARY_DIR}/dep_stb-prefix/src/dep_stb
#                 ${DEP_INSTALL_DIR}/include/stb
#             # ${CMAKE_COMMAND} -E copy
#             #     ${PROJECT_BINARY_DIR}/dep_stb-prefix/src/dep_stb/stb_image.h
#             #     ${DEP_INSTALL_DIR}/include/stb/stb_image.h
#             # COMMAND ${CMAKE_COMMAND} -E copy
#             #     ${PROJECT_BINARY_DIR}/dep_stb-prefix/src/dep_stb/stb_image_write.h
#             #     ${DEP_INSTALL_DIR}/include/stb/stb_image_write.h
#     )
#     set(DEP_LIST ${DEP_LIST} dep_stb)
# endif()

# # assimp
# if (${ASSIMP_USE})
#     ExternalProject_Add(
#         dep_assimp
#         GIT_REPOSITORY "https://github.com/assimp/assimp.git"
#         GIT_TAG "master"
#         GIT_SHALLOW 1
#         UPDATE_COMMAND ""
#         PATCH_COMMAND ""
#         CMAKE_ARGS
#             -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
#             -DBUILD_SHARED_LIBS=OFF
#             -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
#             -DASSIMP_BUILD_TESTS=OFF
#             -DASSIMP_INJECT_DEBUG_POSTFIX=OFF
#             -DASSIMP_BUILD_ZLIB=ON
#         TEST_COMMAND ""
#         )
#     set(DEP_LIST ${DEP_LIST} dep_assimp)
#     set(DEP_LIBS ${DEP_LIBS} libassimp.a)
#     set(DEP_LIBS ${DEP_LIBS} libzlibstatic.a)
# endif()

# # spdlog
# if (${SPDLOG_USE})
#     ExternalProject_Add(
#         dep-spdlog
#         GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
#         GIT_TAG "v1.x"
#         GIT_SHALLOW 1
#         UPDATE_COMMAND ""
#         PATCH_COMMAND ""
#         CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
#         TEST_COMMAND ""
#     )
#     set(DEP_LIST ${DEP_LIST} dep-spdlog)
#     set(DEP_LIBS ${DEP_LIBS} libspdlog.a)
# endif()