#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "initHelper.h"
#include "shaderClass.h"
#include "VBO.h"


int main(){
    // Set up a GLFW window, and init GLAD:
    GLFWwindow* window = glInitHelper::setup(); // Setup function exists just to move all the boilerplate crap out of sight

    // === Defining the geometry and create buffers ===
    // Triangle verts
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Vertex array object
    // The vertex array object (VAO) stores all of the state needed to supply vertex data
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); // Generate 1 VAO
    glBindVertexArray(VAO); // Bind the VAO

    // Vertex buffer object
    // The vertex buffer object (VBO) stores an array of vertices to be sent to the GPU
    VBO vbo(vertices, sizeof(vertices)); // Create a VBO, and put the vertex data in it
    vbo.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Set the vertex attribute pointer
    glEnableVertexAttribArray(0); // Enable the vertex attribute array

    // Create shader program
    shaderClass shader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // Render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader
        shader.use();
        // Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}