	#include "Mesh.h"

	Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <unsigned int>& indices, std::vector <Texture>& textures)
	{
		Mesh::vertices = vertices;
		Mesh::indices = indices;
		Mesh::textures = textures;

		vao.Bind();
		VBO VBO(vertices);
		EBO EBO(indices);
		// Links VBO attributes such as cords and colors to vao
		vao.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
		vao.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
		vao.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
		vao.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

		vao.Unbind();
		VBO.Unbind();
		EBO.Unbind();
	}


	void Mesh::Draw(Shader& shader, Camera& camera)
	{
		// Bind shader to be able to access uniforms
		shader.Activate();
		vao.Bind();

		// Keep track of how many of each type of textures we have
		unsigned int numDiffuse = 0;
		unsigned int numSpecular = 0;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
		    std::string type = textures[i].type;

			if (type == "diffuse")
			{
			    textures[i].texUnit(shader, "material.diffuse", i);
			}
			else if (type == "specular")
			{
			    textures[i].texUnit(shader, "material.specular", i);
			}

		    // shader.setFloat(("material." + type), i);


	    textures[i].Bind(); 
		}
		// Take care of the camera MatrixZ
		glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shader, "camMatrix");

		// Draw the actual mesh
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}