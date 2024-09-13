#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer {
    public:
        IndexBuffer(const void* data, unsigned int count);
        //~IndexBuffer();
        void Bind();
        void Unbind();
        inline unsigned int GetCount() const { return m_Count; }
        unsigned int m_RendererID;
    private:
        unsigned int m_Count;
};
#endif