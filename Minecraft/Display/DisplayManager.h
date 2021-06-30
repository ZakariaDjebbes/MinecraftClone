#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class DisplayManager
{
private:
	const int GL_MAJOR = 4;
	const int GL_MINOR = 6;
	const int GL_PROFILE = GLFW_OPENGL_CORE_PROFILE;

	int screenWidth, screenHeight, interval;
	std::string windowName;
	GLFWwindow* window;

public:
	DisplayManager(int width, int height, const std::string& name, int interval = 1);

	void Update() const;
	void Close() const;
	bool ShouldClose() const;

	inline GLFWwindow* GetWindow() const { return window; }

private:
	static void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity,
		GLsizei length, const char* message, const void* userParam);
};