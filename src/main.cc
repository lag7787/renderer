#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
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
#include "camera.cc"

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 2560;
const unsigned int SCR_HEIGHT = 1440;

Camera camera(glm::vec3(0.0, 0.0f, 3.0f)); // had to declare camera in global scope in oreder for it to be aceessed in callbacks
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const float steps = 10;
const float angle = 3.14159626 * 2.0f / steps;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // api major and minor version that the client must be compatible with
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    Shader ourShader(
        "/home/lucgarabrant/Documents/Projects/openglcc/src/shaders/shader.vs",
        "/home/lucgarabrant/Documents/Projects/openglcc/src/shaders/shader.fs"
    );


//    float vertices[] = {
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };

  //  glm::vec3 cubePositions[] = {
  //      glm::vec3( 0.0f,  0.0f,  0.0f), 
  //      glm::vec3( 2.0f,  5.0f, -15.0f), 
  //      glm::vec3(-1.5f, -2.2f, -2.5f),  
  //      glm::vec3(-3.8f, -2.0f, -12.3f),  
  //      glm::vec3( 2.4f, -0.4f, -3.5f),  
  //      glm::vec3(-1.7f,  3.0f, -7.5f),  
  //      glm::vec3( 1.3f, -2.0f, -2.5f),  
  //      glm::vec3( 1.5f,  2.0f, -2.5f), 
  //      glm::vec3( 1.5f,  0.2f, -1.5f), 
  //      glm::vec3(-1.3f,  1.0f, -1.5f)  
  //  };

    float vertices[] = {
        0.5f, 0.5f, 1.0f,
        0.5f, -0.5f, 1.0f,
        -0.5f, -0.5f, 1.0f, 
        -0.5f, 0.5f, 1.0f
    };

    unsigned int indicies[] = {
        0,1,3,
        1,2,3
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indicies, sizeof(indicies));
    VertexBufferLayout layout;
    layout.Push<float>(3); // Positions
    //layout.Push<float>(2); // Texture
    va.AddBuffer(vb, layout);
    /// dont have to add a buffer for index?

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
    ourShader.setVecTwo("u_res", glm::vec2(SCR_WIDTH, SCR_HEIGHT));

    Renderer ra;
    ra.AddVertexArray(&va.m_RendererID);
    ra.AddBuffer(&vb.m_RendererID);
    ra.AddTexture(&tex1.m_RendererID);
    ra.AddTexture(&tex2.m_RendererID);

    glm::mat4 view;
    glm::mat4 projection = glm::mat4(1.0f);

    float xPos = 0; float yPos = 0; float radius = 1.0f;

    // an iteration of the render loop is called a frame
   while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    ra.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    va.Bind(); 

    float prevX = xPos;
    float prevY = yPos - radius;

    for (int i = 0; i<= steps; i++) {
        
    }

    view = camera.GetViewMatrix();
    ourShader.setMatFour("view", view);
    projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMatFour("projection", projection);
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(0,0,-5));
    //model = glm::scale(model, glm::vec3(3,2,1));
    ourShader.setMatFour("model", model);
    ourShader.setFloat("u_time", glfwGetTime());

    //ra.Draw(GL_TRIANGLES, 6);
    ra.DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT);

   // for (unsigned int i = 0; i < 10; i++) {
   //     glm::mat4 model = glm::mat4(1.0f);
   //     model = glm::translate(model, cubePositions[i]);
   //     float angle = 20.0f * i;
   //     model = glm::rotate(model, glm::radians(angle) , glm::vec3(1.0f, 0.3f, 0.5f));
   //     ourShader.setMatFour("model", model);
   //     ra.Draw(GL_TRIANGLES, 36);
   // }
   // // could we do it with uniforms? 

    glfwSwapBuffers(window);
    glfwPollEvents();
   }

   ra.Cleanup();
   glfwTerminate();
   return 0;
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}   

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

