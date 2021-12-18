#include "texture_object.h"
#include "jpg_readwrite.hpp"

GLuint TextureObject::gen_texture_id(const unsigned char* data, unsigned int width, unsigned int height) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}

std::unique_ptr<unsigned char[]> TextureObject::init_data_from_image(const std::string& texture_name, unsigned int& width, unsigned int& height) {
    std::unique_ptr<unsigned char[]> img{jpg::JpegFile::JpegFileToRGB(texture_name.c_str(), &width, &height)};
    for (int i = 0; i < height/2; i++) {
        for (int j = 0; j < width; j++) {   // flip image vertically for easier OpenGL texture coordinates
            const int pos_a = (i*width+j)*3;
            const int pos_b = ((height-i-1)*width+j)*3;
            std::swap(img[pos_a], img[pos_b]);
            std::swap(img[pos_a + 1], img[pos_b + 1]);
            std::swap(img[pos_a + 2], img[pos_b + 2]);
        }
    }
    return img;
}

TextureObject::~TextureObject() {
    glDeleteTextures(1, &id);
}

void TextureObject::set_texture(const std::string& texture_fname) {
    unsigned int width, height;
    std::unique_ptr<unsigned char[]> img{init_data_from_image(texture_fname, width, height)};
    set_texture(img.get(), width, height);
}

void TextureObject::set_texture(const unsigned char* data, unsigned int width, unsigned int height) {
    glDeleteTextures(1, &id);
    id = gen_texture_id(data, width, height);
}

void TextureObject::bind(void) const {
    glBindTexture(GL_TEXTURE_2D, id);
}

void TextureObject::unbind(void) const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
