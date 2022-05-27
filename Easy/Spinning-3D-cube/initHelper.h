#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// The framebuffer size callback function is called whenever the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height); // Set the viewport to the size of the window
}

namespace glInitHelper{

    void GLFWINIT(){ // Init GLFW and the window hints
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    GLFWwindow* CREATEGLFWWINDOW(char name[]){ // Create window and set context
        GLFWwindow* window = glfwCreateWindow(800, 600, name, NULL, NULL);
        if (window == NULL){
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        return window;
    }

    void INITGLAD(){ // Init GLAD, loads all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }

    GLFWwindow* setup(char name[]){
        GLFWINIT();
        GLFWwindow* window = CREATEGLFWWINDOW(name);
        INITGLAD();
        glViewport(0, 0, 800, 600); // Set glviewport size

        // Set framebuffer size callback
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        return window;
    }

}