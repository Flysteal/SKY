#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
public:
    Texture(const std::string& path, bool flipVertically = true);
    ~Texture();

    // Prevent copying (OpenGL texture IDs should not be copied)
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Move is optional if you plan to store Texture only via shared_ptr
    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    unsigned int GetID() const { return textureID; }

private:
    unsigned int textureID = 0;
    int width = 0, height = 0, nrChannels = 0;
};

#endif
