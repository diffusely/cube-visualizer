#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Callback/Callback.h"

class Window
{
public:

	Window(int width, int height, const char* name);
	~Window();

	void Clear();
	void Update();
	bool ShouldClose() const;

	GLFWwindow* GetNativeWindow() const;


private:
	bool GlfwInit();

private:
	// Window
	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
};