#pragma once
#include<vector>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color; //RGB
	glm::vec2 textureCoords;
};

class VertexBuffer
{
private:
	unsigned int id;
public:
	VertexBuffer(std::vector<Vertex>& verticies);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
