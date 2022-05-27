#pragma once
#include <glad/glad.h>

class EBO {
private:
	unsigned int ID;
	unsigned int m_Size;
public:
	EBO(const unsigned int* data, unsigned int count);
	~EBO();
	void bind() const;
	inline unsigned int getSize() const { return m_Size; }
};
