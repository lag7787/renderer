#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include "glad/glad.h"
#include "glfw3.h"
#include "shader.h"
#include "stb_image.h"
#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"

float face_opacity = 0.5;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}   

void processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        face_opacity += 0.1;
        if (face_opacity >= 1.0) {
            face_opacity = 1.0;
        }
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        face_opacity -= 0.1;
        if (face_opacity <= 0.0) {
            face_opacity = 0.0;
        }
    }
}

int main() {

    // could potentially abstract this as well? init setup? would need to see some best practicves
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // api major and minor version that the client must be compatible with
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    Shader ourShader(
        "/home/lucgarabrant/Documents/Projects/openglcc/src/shaders/shader.vs",
        "/home/lucgarabrant/Documents/Projects/openglcc/src/shaders/shader.fs"
    );

    float vertices[] = {
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // telling each vertex of the rectangle, which part of the texture1 it corresponds to
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3); // Positions
    layout.Push<float>(3); // Color
    layout.Push<float>(2); // Texture
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 6);

    stbi_set_flip_vertically_on_load(true);

    unsigned int texture1;
    glCall(glGenTextures(1, &texture1));
    glCall(glBindTexture(GL_TEXTURE_2D, texture1));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // do i have to do this a second time? 
    int width, height, nrChannels;
    unsigned char* data = stbi_load("/home/lucgarabrant/Documents/Projects/openglcc/assets/container.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        glCall(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glCall(glGenTextures(1, &texture2));
    glCall(glBindTexture(GL_TEXTURE_2D, texture2));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)); // do i have to do this a second time? 
    data = stbi_load("/home/lucgarabrant/Documents/Projects/openglcc/assets/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        glCall(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cout << "Faield to laod texture2" << std::endl;
    }

    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    glfwSetKeyCallback(window, processInput);

   while (!glfwWindowShouldClose(window)) {
       // an iteration of the render loop is called a frame
       // input
       //rendering commands
       ourShader.setFloat("face_opacity", face_opacity);
       glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
       glCall(glClear(GL_COLOR_BUFFER_BIT));
    //   //ourShader.setFloat("horizontalOffset", -0.5);
    //   //ourShader.setFloat("verticalOffset", 0.5);
       glCall(glActiveTexture(GL_TEXTURE0));
       glCall(glBindTexture(GL_TEXTURE_2D, texture1)); // do i have to bind again?
       glCall(glActiveTexture(GL_TEXTURE1));
       glCall(glBindTexture(GL_TEXTURE_2D, texture2)); // do i have to bind again?
       va.Bind();

       //glCall(glBindVertexArray(VAO));

       glCall(glDrawElements(GL_TRIANGLES, 6 ,GL_UNSIGNED_INT, 0));

       // check and call events and swap buffers
       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   glCall(glDeleteVertexArrays(1, &va.m_RendererID));
   glCall(glDeleteBuffers(1, &vb.m_RendererID));
   glCall(glDeleteBuffers(1, &ib.m_RendererID));

   glfwTerminate();
   return 0;
}
