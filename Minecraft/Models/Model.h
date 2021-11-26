#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};

class Model
{
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	VertexBuffer vbo;
	VertexBufferLayout vbLayout;
	VertexArray vao;
	IndexBuffer ebo;

public:
	Model(const std::vector<Vertex> _vertices, 
		const std::vector<unsigned int> _indices, const std::vector<Texture> _textures);
};
