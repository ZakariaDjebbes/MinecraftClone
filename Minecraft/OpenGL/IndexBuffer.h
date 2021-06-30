#pragma once

class IndexBuffer
{
private:
	unsigned int id;
	int count;
public:
	IndexBuffer(const unsigned int* data, unsigned int size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline int GetCount() const { return count; }
};
