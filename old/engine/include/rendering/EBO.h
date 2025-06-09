#ifndef EBO_H
#define EBO_H

#include "glad/gl.h"
#include <vector>


class EBO{
public:
	unsigned int ID;

	EBO(std::vector<unsigned int>& indices);
	~EBO();

	void Bind();
	void Unbind();
	void Delete();

};

#endif