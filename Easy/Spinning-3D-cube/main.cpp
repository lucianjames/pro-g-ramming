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
    char windowName[] = "3D spinning cube";
    GLFWwindow* window = glInitHelper::setup(windowName); // Setup function exists just to move all the boilerplate crap out of sight
    glEnable(GL_DEPTH_TEST);

    // === Defining the geometry ===
    float vertices[] = { // This is a cube
     0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f, // top right
     0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.5f,  0.0f, 0.0f, 0.0f, // top left 

     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // top right
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        0, 4, 1,
        1, 4, 5,
        2, 6, 3,
        3, 6, 7,
        0, 4, 7,
        0, 7, 3,
        1, 5, 6,
        1, 6, 2
    };

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

    // === Define transforms ===
    int m_viewport[4];
    glGetIntegerv(GL_VIEWPORT, m_viewport);
    glm::mat4 model = glm::mat4(1.0f); // Define a model matrix for the square
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
    glm::mat4 view = glm::mat4(1.0f); // Define a view matrix for the scene
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f)); // note that we're translating the scene in the reverse direction of where we want to move
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f); // Define the perspective projection matrix

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // === Unbind/reset stuff (best practice or something) ===
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // === Render ===
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Set the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
        vertexArray.bind(); // Bind the VAO
        indexBuffer.bind(); // Bind the EBO
        shader.use(); // Use the shader program
        // Transforms:
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.25f, 0.5f, 0.75f)); // Rotate the square
        glGetIntegerv(GL_VIEWPORT, m_viewport); // Get the viewport size (maybe code to only do upon resize?)
        perspective = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f); // Update the perspective projection matrix
        shader.setUniformMat4fv("model", glm::value_ptr(model)); // Set the model matrix
        shader.setUniformMat4fv("view", glm::value_ptr(view)); // Set the view matrix
        shader.setUniformMat4fv("projection", glm::value_ptr(perspective)); // Set the projection matrix
        // Actualy draw some triangles
        glDrawElements(GL_TRIANGLES, indexBuffer.getSize(), GL_UNSIGNED_INT, nullptr);

        // === Swap buffers ===
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}