#include "Texture.h"
#include "stb_image.h"
#include <glad/gl.h>
#include <iostream>

Texture::Texture(const std::string& path, bool flipVertically)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(flipVertically);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        std::cout << "Texture loaded: " << path  << " (" << width << "x" << height << ", " << nrChannels << " channels)\n";

        GLenum format = GL_RGB;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture()
{
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}

// Move constructor
Texture::Texture(Texture&& other) noexcept
    : textureID(other.textureID), width(other.width), height(other.height), nrChannels(other.nrChannels)
{
    other.textureID = 0;
    other.width = 0;
    other.height = 0;
    other.nrChannels = 0;
}

// Move assignment operator
Texture& Texture::operator=(Texture&& other) noexcept
{
    if (this != &other) {
        if (textureID != 0)
            glDeleteTextures(1, &textureID);

        textureID = other.textureID;
        width = other.width;
        height = other.height;
        nrChannels = other.nrChannels;

        other.textureID = 0;
        other.width = 0;
        other.height = 0;
        other.nrChannels = 0;
    }
    return *this;
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
