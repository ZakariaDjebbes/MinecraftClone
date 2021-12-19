#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "../Camera/FPSCamera.h"
#include "../Renderer/Renderer.h"

class Mesh
{
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	VertexArray va;
	IndexBuffer ib;

public:
	Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture>& _textures);
	~Mesh();

	void Draw(Shader& shader, FPSCamera& camera, Renderer& renderer) const;
};
