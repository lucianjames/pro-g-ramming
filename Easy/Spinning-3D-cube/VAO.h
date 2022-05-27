#include <glad/glad.h>
#include "VBO.h"
#include "VBO_layout.h"

class VAO{
private:
    unsigned int ID;
public:
    VAO();
    ~VAO();
    void bind();
    void addBuffer(VBO& vbo, const VBO_layout& layout);
};