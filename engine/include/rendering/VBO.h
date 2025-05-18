#ifndef VBO_H
#define VBO_H

#include "glad/gl.h"

class VBO{
public:
	unsigned int ID;

    VBO(float* vertices, GLsizeiptr size);
	~VBO();

	void Bind();
	void Unbind();
	void Delete();

};

#endif