#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/Shader.h"

class Renderer
{
public:
	void Clear(float r, float g, float b, float a) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Draw(const VertexArray& va, const Shader& shader, const int count) const;
};
