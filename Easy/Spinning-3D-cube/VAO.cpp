#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

VAO::~VAO(){
    glDeleteVertexArrays(1, &ID);
}

void VAO::bind(){
    glBindVertexArray(ID);
}

void VAO::addBuffer(VBO& vbo, const VBO_layout& layout){
    this->bind(); // Bind the VAO
    vbo.bind(); // Bind the VBO
    const auto& elements = layout.getElements(); // Get the elements from the layout
    unsigned long long int offset = 0; // long long int is used to avoid overflow under basically any circumstance
    for (int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i]; // Get the element
        glEnableVertexAttribArray(i); // Enable the attribute
        glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.getStride(), (const void*)offset); // Set the attribute
        offset += element.count * VBO_element::getSizeOfType(element.type); // Increase the offset
    }
}