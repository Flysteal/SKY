#include "Texture.h"
#include <iostream>
#include <algorithm>


Texture::Texture() = default;
Texture::~Texture() { Delete(); }

void Texture::Init(const std::string& image, unsigned int texType, int slot, unsigned int pixelType)
{
    size_t dotPos = image.find_last_of('.');
    if (dotPos == std::string::npos) {
        std::cout << "no extension\n";
        return;
    }

    std::string extension = image.substr(dotPos); // includes the dot
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower); // lowercase for consistency

    type = texType;
    t_slot = slot;

    stbi_set_flip_vertically_on_load(false);

    int widthImg, heightImg, numColCh;
    int desiredChannels = 0;

    if (extension == ".jpga" || extension == ".pnga") {
        desiredChannels = 1;
    }

    unsigned char* bytes = stbi_load(image.c_str(), &widthImg, &heightImg, &numColCh, desiredChannels);
    if (!bytes) {
        std::cerr << image << " failed to load\n";
        return;
    }

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (extension == ".png" || extension == ".pnga") {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, pixelType, bytes);
    } else if (extension == ".jpg" || extension == ".jpga") {
        glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, pixelType, bytes);
    } else {
        std::cout << "unknown type\n";
        stbi_image_free(bytes);
        glBindTexture(texType, 0);
        return;
    }

    glGenerateMipmap(texType);
    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}


void Texture::texUnit(Shader& shader, const char* uniform, unsigned int unit)
{
    unsigned int texUni = glGetUniformLocation(shader.ID, uniform);
    // Shader needs to be activated before changing the value of a uniform
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind(){
    glActiveTexture(t_slot);
    glBindTexture(type, ID);
}

void Texture::Unbind(){
    glBindTexture(type, 0);
}

void Texture::Delete(){
    glDeleteTextures(1, &ID);
}