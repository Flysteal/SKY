#ifndef MESH_H
#define MESH_H

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector <Vertex> vertices;
	std::vector <unsigned int> indices;
	std::vector <Texture> textures;

	VAO vao;

	Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
};
#endif