#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<vector>
#include "VertexBuffer.h"
#include <stdexcept>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
};

struct VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout() : stride(0)
	{

	}

	void AddElements(unsigned int type, unsigned int count, unsigned char normalized = GL_FALSE)
	{
		elements.push_back({ type, count, normalized });
		stride += GlTypeToSize(type) * count;
	}

	static unsigned int GlTypeToSize(unsigned int type)
	{
		switch (type)
		{
		case GL_UNSIGNED_INT: case GL_FLOAT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		default:
			throw std::invalid_argument("unsupported type in vertex array");
		}
	}


	const std::vector<VertexBufferElement> GetElements() const& { return elements; }
	inline unsigned int GetStride() const { return stride; }
};

class VertexArray
{
private:
	unsigned int id;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void BindBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
