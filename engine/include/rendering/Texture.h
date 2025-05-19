#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/gl.h>
#include "stb_image.h"

#include"Shader.h"
#include <string>
#include <iostream>

class Texture
{
public:
	unsigned int ID;

	Texture();
	~Texture();

	void Init(const std::string& image,unsigned int texType, int slot, unsigned int pixelType);

	void texUnit(Shader& shader, const char* uniform, unsigned int unit);
	void Bind();
	void Unbind();
	void Delete();
private:
	unsigned int type;
	unsigned int t_slot;
};
#endif