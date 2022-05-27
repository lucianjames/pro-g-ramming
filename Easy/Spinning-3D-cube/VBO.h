#pragma once
#include <glad/glad.h>

class VBO {
private:
    unsigned int ID;
public:
    VBO(float* vertices, unsigned int size);
    ~VBO();
    void bind();
};