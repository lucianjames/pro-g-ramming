#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "initHelper.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VBO_layout.h"
#include "VAO.h"
#include "EBO.h"

int main(){
    // === Set up a GLFW window, and init GLAD ===
    GLFWwindow* window = glInitHelper::setup(); // Setup function exists just to move all the boilerplate crap out of sight

    // === Defining the geometry ===
    float vertices[] = { // This is a square
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// top right
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 0.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    glm::mat4 transform = glm::mat4(1.0f); // Define a transformation matrix for the square (this is update every frame in the rendering loop)

    // === Set up VBO, VBO layout, IBO, VAO, EBO ===
    VBO vertexBuffer(vertices, sizeof(vertices)); // The VBO store the vertex data to be sent to the GPU
    VBO_layout layout; // This is a struct that defines the layout of the VBO
    layout.pushFloat(3); // Position data
    layout.pushFloat(3); // Color data
    VAO vertexArray; // The VAO stores all of the state needed to supply vertex data
    EBO indexBuffer(indices, sizeof(indices)); // The EBO stores the indices to be sent to the GPU
    vertexArray.addBuffer(vertexBuffer, layout);

    // === Create shader program ===
    shaderClass shader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // Unbind/reset stuff (best practice or something):
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // Render:
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set the background color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
        vertexArray.bind(); // Bind the VAO
        indexBuffer.bind(); // Bind the EBO
        shader.use(); // Use the shader program
        transform = glm::rotate(transform, (float)glfwGetTime()/100, glm::vec3(0.0f, 0.0f, 1.0f)); // Transform calculation (spin faster as time goes on)
        shader.setUniformMat4fv("transform", glm::value_ptr(transform)); // Send the transform matrix to the shader
        glDrawElements(GL_TRIANGLES, indexBuffer.getSize(), GL_UNSIGNED_INT, nullptr); // Draw the triangle

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}