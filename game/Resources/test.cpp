#include "Texture.h"
#include <iostream>


Texture::Texture() = default;
Texture::~Texture() { Delete(); }


void Texture::Init(const std::string& image,unsigned int texType, int slot, unsigned int pixelType)
{
    size_t dotPos = image.find_last_of('.');
    if (dotPos != std::string::npos) 
    {
        std::string extension = image.substr(dotPos); // includes the dot
        int widthImg, heightImg, numColCh; 

        if (extension == ".jpg")
        {
            t_slot = slot;
            format = GL_RGB;
            numColCh = 3;
        }
        if (extension == ".jpgA")
        {
            t_slot = slot;
            format = GL_RED;
            numColCh = 1;
        }
        if (extension == ".png")
        {
            t_slot = slot;
            format = GL_RGBA;
            numColCh = 4;
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        if (extension == ".pngA")
        {
            t_slot = slot;
            format = GL_RED;
            numColCh = 1;
        }
        else{
        std::cout << "unknown type\n";
        }

        unsigned char* bytes = stbi_load(image.c_str(), &widthImg, &heightImg, &numColCh, 0);

        stbi_set_flip_vertically_on_load(false);

        if(!bytes){
            std::cerr << image << "Failed to load\n";
            return;
        }

        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(texType, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
        glGenerateMipmap(texType);

        stbi_image_free(bytes);
        glBindTexture(texType, 0);


    }
    else{
    std::cout << "no extension\n";
    }
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