#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "../Camera/FPSCamera.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color; //RGB
	glm::vec2 textureCoords;
};

class Mesh
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
	Mesh(const std::vector<Vertex>& _vertices,
		const std::vector<unsigned int>& _indices, const std::vector<Texture>& _textures);
	~Mesh();

	void Draw(Shader& shader, FPSCamera& camera) const;
};
