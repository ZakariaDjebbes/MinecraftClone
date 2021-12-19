#pragma once
#include <vector>

class IndexBuffer
{
private:
	unsigned int id;
	int count;
public:
	IndexBuffer(const unsigned int* indicies, const unsigned int size);
	IndexBuffer(std::vector<unsigned int> indicies);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline int GetCount() const { return count; }
};
