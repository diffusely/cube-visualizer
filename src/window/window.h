#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

class Window
{
public:

	Window(int width, int height, const char* name);
	~Window();

	GLFWwindow* get_window() const;
	

private:
	bool glfw_init();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
	GLFWwindow* m_window;

};