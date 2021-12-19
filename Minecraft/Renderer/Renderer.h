#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/IndexBuffer.h"
#include "../OpenGL/Shader.h"

class Renderer
{
public:
	void Clear(const float& r, const float& g, const float& b, const float& a) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void DrawArray(const VertexArray& va, const Shader& shader, const int count) const;
};
