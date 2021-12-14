#include "texture.h"
#include "jpg_readwrite.hpp"

std::unique_ptr<unsigned char[]> Texture::init_data_from_image(const std::string& texture_name, unsigned int& width, unsigned int& height) {
    return std::unique_ptr<unsigned char[]>( jpg::JpegFile::JpegFileToRGB(texture_name.c_str(), &width, &height) );
}

GLuint Texture::gen_texture_id(const std::unique_ptr<unsigned char[]>& data, unsigned int width, unsigned int height) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.get());
    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}

Texture::Texture(const std::string& texture_name) {
    std::unique_ptr img = init_data_from_image(texture_name, width, height);
    data.swap(img);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind(void) {
    if (id == 0) {
        id = gen_texture_id(data, width, height);
    }
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind(void) const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
