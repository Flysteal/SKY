#ifndef VAO_H
#define VAO_H

#include "glad/gl.h"
#include "VBO.h"

class VAO{
public:
	unsigned int ID;

	VAO();
	~VAO();

	void LinkAttrib(VBO& VBO, unsigned int layout, unsigned int numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();

private:
};

#endif