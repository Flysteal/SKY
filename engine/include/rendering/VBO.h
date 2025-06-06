#ifndef VBO_H
#define VBO_H

#include "glad/gl.h"
#include "glm/glm.hpp"
#include <vector>
#include "Vertex.h"


class VBO
{
public:
	unsigned int ID;

    VBO(std::vector<Vertex>& vertices);
	~VBO();

	void Bind();
	void Unbind();
	void Delete();

};

#endif