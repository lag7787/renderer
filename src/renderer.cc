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