#include "texture.h"
#include "renderer.h"
#include <iostream>

// we could potentially parametrize the constructor, but i think this works for now
// we can also assign this texture a number representing its texture unit
// then too how should this relate to the shader code? 

// i hate these parameter names but we can try different later
Texture::Texture(unsigned int a, unsigned int b, int c) : type(a), texture_unit(b), texture_number(c) {
    glCall(glGenTextures(1, &m_RendererID));
    glCall(glActiveTexture(texture_unit));
    glCall(glBindTexture(type, m_RendererID)); // right now this is only for a 2D texture, which i guess is the only abstraction we need
}

void Texture::Bind() {
    // will also call the texture unit this corresponds to
    glCall(glActiveTexture(texture_unit));
    glCall(glBindTexture(type, m_RendererID));
}

//almost want to do an array of binds
void Texture::AddParameter(unsigned int name, unsigned int param) {
    Bind();
    glCall(glTexParameteri(type, name, param));
}

void Texture::BuildImage(int width, int height, unsigned char* data, unsigned int internal_foramt, unsigned int format) {
        glCall(glTexImage2D(type, 0, internal_foramt, width, height, 0, format, GL_UNSIGNED_BYTE, data));
}

void Texture::GenerateMipMip() {
        glCall(glGenerateMipmap(type));
}

