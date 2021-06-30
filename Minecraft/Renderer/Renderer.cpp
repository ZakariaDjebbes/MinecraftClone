#include "Renderer.h"
#include <iostream>

void Renderer::Clear(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Use();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(const VertexArray& va, const Shader& shader, const int count) const
{
	va.Bind();
	shader.Use();

	glDrawArrays(GL_TRIANGLES, 0, count);
}
