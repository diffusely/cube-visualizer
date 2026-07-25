cmake_minimum_required(VERSION 3.20)

project(cube-visualizer LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Output
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
 "src/window/window.h" "src/window/window.cpp")


# -----------------------------
# Copy shaders folder
# -----------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)


# -----------------------------
# Include directories
# -----------------------------
target_include_directories(${PROJECT_NAME} PRIVATE

    src

    src/graphics/IndexBuffer
    src/graphics/VertexBuffer
    src/graphics/VertexArray
    src/graphics/Shader
    src/window

    libs
    libs/glad/include
    libs/glfw/include

)


# -----------------------------
# GLAD
# -----------------------------
add_library(glad STATIC

    libs/glad/src/glad.c

 )

target_include_directories(glad PUBLIC

    libs/glad/include

)

target_link_libraries(${PROJECT_NAME}

    glad

)


# -----------------------------
# GLFW
# -----------------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")

add_subdirectory(libs/glfw)

target_link_libraries(${PROJECT_NAME}

    glfw

)


# -----------------------------
# OpenGL
# -----------------------------
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}

    OpenGL::GL

)


# -----------------------------
# Windows DLL
# -----------------------------
if(WIN32)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_if_different

        $<TARGET_FILE:glfw>

        $<TARGET_FILE_DIR:${PROJECT_NAME}>

    )

endif()