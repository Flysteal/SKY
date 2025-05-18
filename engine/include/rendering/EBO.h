#ifndef EBO_H
#define EBO_H

#include "glad/gl.h"

class EBO{
public:
	unsigned int ID;

	EBO(unsigned int* indices, GLsizeiptr size);
	~EBO();

	void Bind();
	void Unbind();
	void Delete();

};

#endif