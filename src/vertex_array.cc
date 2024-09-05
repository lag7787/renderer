#include "vertex_array.h"
#include "renderer.h"

VertexArray::VertexArray() {
    glCall(glGenVertexArrays(1, &m_RendererID));
    glCall(glBindVertexArray(m_RendererID));
}
void VertexArray::AddBuffer(VertexBuffer& vb, VertexBufferLayout& layout) {
    Bind();
    vb.Bind();
    auto& elements = layout.GetElements();
    long offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        glCall(glVertexAttribPointer(i,element.count,element.type, element.normalized, layout.GetStride(), (const void*) offset));
        glCall(glEnableVertexAttribArray(i));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() {
    glCall(glBindVertexArray(m_RendererID));
}