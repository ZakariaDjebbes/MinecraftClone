#pragma once
#include <string>

class Texture
{
private:
	unsigned int id;
	unsigned char* localBuffer;
	int width, height, bpp;
	std::string filePath;
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};

