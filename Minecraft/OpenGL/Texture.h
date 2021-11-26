#pragma once
#include <string>

enum class TextureType {
	Diffuse = 0,
	Specular = 1
};

class Texture
{
private:
	unsigned int id;
	unsigned char* localBuffer;
	int width, height, bpp;
	std::string filePath;
	TextureType type;
public:
	Texture(const std::string& _filePath, const TextureType _type = TextureType::Diffuse);
	~Texture();

	void Bind(const unsigned int slot) const;
	void Bind() const;
	void Unbind();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
	inline TextureType GetType() const { return type; }
};

