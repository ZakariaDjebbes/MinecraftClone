#include "Model.h"

Model::Model(const std::vector<Vertex> _vertices, 
	const std::vector<unsigned int> _indices, const std::vector<Texture> _textures)
	: vertices(_vertices), indices(_indices), 
	textures(_textures), 
	vbo(&_vertices[0], vertices.size() * sizeof(Vertex)), 
	ebo(&_indices[0], sizeof(_indices))
{
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 2);
	vao.BindBuffer(vbo, vbLayout);
}
