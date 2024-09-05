#pragma once

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {

    public:
        VertexArray();
        void AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout);
        void Bind(); // what is a const function? 
        unsigned int m_RendererID;

};