#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "glfw3.h"
#include "shader.h"
#include "stb_image.h"
#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "texture.h"

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
    std::cout <<"hello, world" << std::endl;
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

    Texture tex1(GL_TEXTURE_2D, GL_TEXTURE1, 1);
    tex1.AddParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex1.AddParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex1.AddParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex1.AddParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;

    unsigned char* data = stbi_load("/home/lucgarabrant/Documents/Projects/openglcc/assets/container.jpg", &width, &height, &nrChannels, 0);
    if(data) {
        tex1.BuildImage(width, height, data, GL_RGB, GL_RGB);
        tex1.GenerateMipMip();
    } else {
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free(data);

    Texture tex2(GL_TEXTURE_2D, GL_TEXTURE2, 2);
    tex2.AddParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    tex2.AddParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
    tex2.AddParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    tex2.AddParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("/home/lucgarabrant/Documents/Projects/openglcc/assets/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        tex2.BuildImage(width, height, data, GL_RGBA, GL_RGBA);
        tex1.GenerateMipMip();
    } else {
        std::cout << "Faield to laod texture2" << std::endl;
    }

    stbi_image_free(data);


    ourShader.use();
    ourShader.setInt("texture1", tex1.GetTextureNumber()); //creating a unifrom to refernce texture units? 
    ourShader.setInt("texture2", tex2.GetTextureNumber());
    glfwSetKeyCallback(window, processInput);

    Renderer ra;
    ra.AddVertexArray(&va.m_RendererID);
    ra.AddBuffer(&vb.m_RendererID);
    ra.AddBuffer(&ib.m_RendererID);
    ra.AddTexture(&tex1.m_RendererID);
    ra.AddTexture(&tex2.m_RendererID);

    // an iteration of the render loop is called a frame
   while (!glfwWindowShouldClose(window)) {
       glm::mat4 trans = glm::mat4(1.0f);
       trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
       trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
       ourShader.setMatFour("transform", trans);
       ourShader.setFloat("face_opacity", face_opacity);
       ra.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    //   ourShader.setFloat("horizontalOffset", -0.5);
    //   ourShader.setFloat("verticalOffset", 0.5);
       va.Bind();
       ra.Draw(GL_TRIANGLES, 6, GL_UNSIGNED_INT);
       glfwSwapBuffers(window);
       glfwPollEvents();
   }

   ra.Cleanup();
   glfwTerminate();
   return 0;
}
