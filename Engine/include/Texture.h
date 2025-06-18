#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
public:
    Texture(const std::string& path, bool flipVertically = true);
    ~Texture();

    // Delete copy constructor and copy assignment
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Allow move constructor and move assignment
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline unsigned int GetID() const { return textureID; }

private:
    unsigned int textureID = 0;
    int width = 0, height = 0, nrChannels = 0;
};

#endif
