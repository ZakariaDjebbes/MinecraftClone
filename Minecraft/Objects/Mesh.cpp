#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture>& _textures)
	: vertices(_vertices), indices(_indices), textures(_textures), ib(IndexBuffer(indices))
{
	VertexBuffer vb(vertices);
	VertexBufferLayout vbLayout;
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 3);
	vbLayout.AddElements(GL_FLOAT, 2);

	ib.Bind();
	va.BindBuffer(vb, vbLayout);

	vb.Unbind();
	va.Unbind();
	ib.Unbind();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader& shader, FPSCamera& camera, Renderer& renderer) const
{
	shader.Use();
	va.Bind();

	for (auto& texture : textures)
		texture.Bind();

	shader.setMatrix4f("view", camera.GetView());
	shader.setMatrix4f("proj", camera.GetProjection());

	renderer.Draw(va, ib, shader);
}