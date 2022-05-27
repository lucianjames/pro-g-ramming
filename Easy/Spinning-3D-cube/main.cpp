#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "initHelper.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VBO_layout.h"
#include "VAO.h"


int main(){
    // === Set up a GLFW window, and init GLAD ===
    GLFWwindow* window = glInitHelper::setup(); // Setup function exists just to move all the boilerplate crap out of sight

    // === Defining the geometry ===
    float vertices[] = { // This is a triangle
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // === Set up VBO, VBO layout, IBO, VAO ===
    VBO vertexBuffer(vertices, 3 * 3 * sizeof(float));
    VBO_layout layout; // This is a struct that defines the layout of the VBO
    layout.pushFloat(3); // Position data
    VAO vertexArray;
    vertexArray.addBuffer(vertexBuffer, layout);

    // === Create shader program ===
    shaderClass shader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // Unbind stuff:
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the background color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

        vertexArray.bind(); // Bind the VAO
        shader.use(); // Use the shader
        glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}