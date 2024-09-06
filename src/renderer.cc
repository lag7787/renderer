#include "renderer.h"
#include <iostream>

void glClearError() {

    while (glGetError() != GL_NO_ERROR);
}

const char* glTranslateError(GLenum error) {

    if (error == 0x0500) {
        return "GL_INVALID_ENUM";
    } else {

        return "GL_ERROR";
    }
}
bool glLogCall(const char* function, const char* file, int line) {

    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] : " << glTranslateError(error) << " -> " << function << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

void Renderer::Cleanup() {
    for (unsigned int i = 0; i < vertexArrays.size(); i++) {
            glCall(glDeleteVertexArrays(1, vertexArrays[i]));
    }

    for (unsigned int i = 0; i < buffers.size(); i++) {
            glCall(glDeleteBuffers(1, buffers[i]));
    }

    for (unsigned int i = 0; i < textures.size(); i++) {
            glCall(glDeleteBuffers(1, textures[i]));
    }
}

void Renderer::ClearColor(float red, float green, float blue, float alpha) {
       glCall(glClearColor(red, green, blue, alpha));
       glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(unsigned int mode, int count, unsigned int type) {
       glCall(glDrawElements(mode, count ,type, 0));
}

void Renderer::AddVertexArray(unsigned int * id) {
    vertexArrays.push_back(id);
}
void Renderer::AddBuffer(unsigned int * id) {
    buffers.push_back(id);
}
void Renderer::AddTexture(unsigned int * id) {
    textures.push_back(id);
}