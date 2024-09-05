#include "glad/glad.h"
#include "glfw3.h"
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer {
    private:
    public:
        VertexBuffer(const void* data, unsigned int size);
        //~VertexBuffer();
        void Bind();
        void Unbind();
        unsigned int m_RendererID;
};
#endif