#include "Texture.h"
#include <iostream>

Texture::~Texture() { Delete(); }

Texture::Texture(const std::string& image, const char* texType, int slot, unsigned int texUnit, unsigned int pixelType)
{
    type = texType;
    t_slot = texUnit;

    size_t dotPos = image.find_last_of('.');
    if (dotPos == std::string::npos) {
        std::cerr << "Texture error: No file extension found in '" << image << "'\n";
        return;
    }

    std::string extension = image.substr(dotPos);
    bool hasAlpha = (extension == ".png");

    stbi_set_flip_vertically_on_load(true);  // Flip vertically for OpenGL

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

    GLenum format;
    if (channels == 1)
        format = GL_RED;
    else if (channels == 3)
        format = GL_RGB;
    else if (channels == 4)
        format = GL_RGBA;
    else {
        std::cerr << "Unsupported number of channels: " << channels << "\n";
        stbi_image_free(data);
        return;
    }

    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pixelType, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    // std::cout << "Loaded texture: " << image << ", Width: " << width << ", Height: " << height << ", Channels: " << channels << '\n';

}

void Texture::texUnit(Shader& shader, const std::string& uniform, unsigned int unit) {
    shader.Activate();
    glUniform1i(glGetUniformLocation(shader.ID, uniform.c_str()), unit);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + t_slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete() {
    glDeleteTextures(1, &ID);
}