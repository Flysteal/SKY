// Texture.h
#pragma once
#include <string>
#include <glad/gl.h>

class Texture {
public:
    Texture(const std::string& path, bool flipVertically = true);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline unsigned int GetID() const { return textureID; }

private:
    unsigned int textureID;
    int width, height, nrChannels;
};
