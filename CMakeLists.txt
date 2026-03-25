
cmake_minimum_required(VERSION 3.20)
project(cube-visualizer LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Output folder for executable
# -----------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# -----------------------------
# Source files
# -----------------------------
file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
    src/graphics/IndexBuffer/*.cpp
    src/graphics/VertexBuffer/*.cpp
    src/graphics/VertexArray/*.cpp
    src/graphics/Shader/*.cpp
)

# Graphics module documentation
install(FILES src/graphics/README.md DESTINATION share/graphics)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCES})

file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/shaders/*")
foreach(SHADER ${SHADERS})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endforeach()

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    src
    src/graphics/IndexBuffer
    src/graphics/VertexBuffer
    src/graphics/VertexArray
    src/graphics/Shader
    libs/glad/include
    libs/glfw/include
    libs/glm
)

# -----------------------------
# GLAD
# -----------------------------
add_library(glad STATIC
    libs/glad/src/glad.c
)
target_include_directories(glad PUBLIC libs/glad/include)
target_link_libraries(${PROJECT_NAME} glad)

# -----------------------------
# GLFW
# -----------------------------
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "" )
set(GLFW_BUILD_TESTS    OFF CACHE INTERNAL "" )
set(GLFW_BUILD_DOCS     OFF CACHE INTERNAL "" )

add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# -----------------------------
# OpenGL
# -----------------------------
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# -----------------------------
# Windows: copy DLL (if using GLFW as DLL)
# -----------------------------
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:glfw>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
