#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "initHelper.h"
#include "shaderClass.h"
#include "VBO.h"
#include "VBO_layout.h"
#include "VAO.h"


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
    VAO vao;

    // Set up VBO, VBO layout, IBO, VAO
    VBO vertexBuffer(vertices, 3 * 3 * sizeof(float));
    VBO_layout layout;
    layout.pushFloat(3); // Position data
    VAO vertexArray;
    vertexArray.addBuffer(vertexBuffer, layout);

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