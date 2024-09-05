#include "index_buffer.h"
#include "renderer.h"


IndexBuffer::IndexBuffer(const void* data, unsigned int count) : m_Count(count) {

    glCall(glGenBuffers(1, &m_RendererID));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

//IndexBuffer::~IndexBuffer() {
//    glCall(glDeleteBuffers(1, &m_RendererID));
//
//}
void IndexBuffer::Bind() {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}