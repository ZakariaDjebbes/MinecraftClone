#include "Renderer.h"
#include <iostream>

void Renderer::Clear(const float& r, const float& g, const float& b, const float& a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	shader.Use();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawArray(const VertexArray& va, const Shader& shader, const int count) const
{
	va.Bind();
	shader.Use();

	glDrawArrays(GL_TRIANGLES, 0, count);
}