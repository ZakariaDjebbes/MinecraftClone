#include "IndexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

IndexBuffer::IndexBuffer(const unsigned int* indicies, const unsigned int size) : count(size / sizeof(unsigned int))
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(std::vector<unsigned int> indicies) : count((indicies.size() * sizeof(unsigned int) / sizeof(unsigned int)))
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int), indicies.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}