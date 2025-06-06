#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/gl.h>
#include "stb_image.h"

#include "Shader.h"
#include <string>
#include <iostream>

class Texture
{
public:
	unsigned int ID;
	const char* type;

	Texture(const std::string& image, const char* texType, int slot, unsigned int t_slot, unsigned int pixelType);
	~Texture();

	void texUnit(Shader& shader, const std::string& uniform, unsigned int unit);
	void Bind();
	void Unbind();
	void Delete();
private:
	unsigned int format;
	unsigned int t_slot;
};
#endif