#include "Texture.h"
#include <iostream>


Texture::Texture() = default;
Texture::~Texture() { Delete(); }

void Texture::Init(const std::string& image, unsigned int texType, int slot, unsigned int pixelType) {
    type = texType;
    t_slot = slot;

    // Extract file extension
    size_t dotPos = image.find_last_of('.');
    if (dotPos == std::string::npos) {
        std::cerr << "Texture error: No file extension found in '" << image << "'\n";
        return;
    }

    std::string extension = image.substr(dotPos);
    bool hasAlpha = (extension == ".png");

    stbi_set_flip_vertically_on_load(false);

    if (hasAlpha) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    int width, height, channels;
    unsigned char* data = stbi_load(image.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << image << "\n";
        return;
    }

    GLenum format = hasAlpha ? GL_RGBA : GL_RGB;

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Texture Wrapping and Filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(texType, 0, format, width, height, 0, format, pixelType, data);
    glGenerateMipmap(texType);

    stbi_image_free(data);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, unsigned int unit) {
    shader.Activate();
    glUniform1i(glGetUniformLocation(shader.ID, uniform), unit);
}

void Texture::Bind() {
    glActiveTexture(t_slot);
    glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}