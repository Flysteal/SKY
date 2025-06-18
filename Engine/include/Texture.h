#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

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

#endif