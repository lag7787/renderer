#ifndef TEXTURE
#define TEXTURE

class Texture {
    private:
        unsigned int type;
        unsigned int texture_unit;
        int texture_number;
    public:
        Texture(unsigned int, unsigned int, int);
        void Bind();
        void AddParameter(unsigned int, unsigned int);
        void BuildImage(int, int, unsigned char*, unsigned int, unsigned int);
        void GenerateMipMip();
        unsigned int m_RendererID;
        inline int GetTextureNumber() const {return texture_number;}
};
#endif