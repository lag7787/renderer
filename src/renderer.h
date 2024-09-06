#pragma once
#include "glad/glad.h"
#include <signal.h>
#include <vector>

#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define glCall(x) glClearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__));


void glClearError();
const char* glTranslateError(GLenum error);
bool glLogCall(const char* function, const char* file, int line);


class Renderer {

    public:
        std::vector<unsigned int*> vertexArrays;
        std::vector<unsigned int*> buffers;
        std::vector<unsigned int*> textures;

        void Cleanup();
        void ClearColor(float red, float green, float blue, float alpha);
        void Draw(unsigned int mode, int count, unsigned int type);
        void AddVertexArray(unsigned int * id);
        void AddBuffer(unsigned int * id);
        void AddTexture(unsigned int * id);
};