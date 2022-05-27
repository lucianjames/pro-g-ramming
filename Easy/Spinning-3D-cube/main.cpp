#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderClass.h"
#include "VBO.h"

// The framebuffer size callback function is called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height); // Set the viewport to the size of the window
}

int main(){

    // Init GLFW and the window hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window and set context
    GLFWwindow* window = glfwCreateWindow(800, 600, "WindowTitle", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Init glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set glviewport size
    glViewport(0, 0, 800, 600);

    // Set framebuffer size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


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
    VBO vbo(vertices, sizeof(vertices));
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