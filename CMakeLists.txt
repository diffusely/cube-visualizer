cmake_minimum_required(VERSION 3.20)

project(cube-visualizer LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# -----------------------------
# C++
# -----------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Output
# -----------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# Source files
# -----------------------------
file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
    libs/stb/stb.cpp
)

add_executable(${PROJECT_NAME}
    ${ENGINE_SOURCES}
)

# -----------------------------
# Copy resources
# -----------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(${PROJECT_NAME} PRIVATE

    src

    libs

    libs/glad/include
    libs/glfw/include

    libs/imgui
    libs/imgui/backends
)

# =========================================================
# GLAD
# =========================================================
add_library(glad STATIC
    libs/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    libs/glad/include
)

# =========================================================
# GLFW
# =========================================================
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")

add_subdirectory(libs/glfw)

# =========================================================
# OpenGL
# =========================================================
find_package(OpenGL REQUIRED)

# =========================================================
# ImGui
# =========================================================
add_library(imgui STATIC

    libs/imgui/imgui.cpp
    libs/imgui/imgui_draw.cpp
    libs/imgui/imgui_demo.cpp
    libs/imgui/imgui_impl_glfw_gl3.cpp
)

target_include_directories(imgui PUBLIC

    libs/imgui
    libs/imgui/backends

    libs/glfw/include
    libs/glad/include
)

target_link_libraries(imgui PUBLIC

    glfw
    OpenGL::GL

)

# =========================================================
# Link libraries
# =========================================================
target_link_libraries(${PROJECT_NAME}

    glad
    glfw
    imgui
    OpenGL::GL

)

# =========================================================
# Copy glfw.dll
# =========================================================
if(WIN32)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:glfw>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>

    )

endif()