    #include "Mesh.h"
    #include <glad/gl.h>

Mesh::Mesh(std::vector<Vertex> vertices,    std::vector<unsigned int> indices, std::vector<Texture> textures, Material material)
    : vertices(vertices), indices(indices), textures(textures), material(material)
{
    setupMesh();
}

    void Mesh::setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // Vertex Texture Coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        
        glEnableVertexAttribArray(3); // assuming 0=position, 1=normal, 2=texcoord
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));


        glBindVertexArray(0);
    }

    void Mesh::Draw(Shader& shader) {
        unsigned int diffuseNr = 1;

        shader.setVec3("material.ambient", material.ambient);
        shader.setVec3("material.diffuse", material.diffuse);
        shader.setVec3("material.specular", material.specular);
        shader.setFloat("material.shininess", material.shininess);
        shader.setVec3("dirLight.direction",  glm::vec3(-0.2f, -1.0f, -0.3f));
shader.setVec3("dirLight.ambient",    glm::vec3(0.1f));
shader.setVec3("dirLight.diffuse",    glm::vec3(0.5f));
shader.setVec3("dirLight.specular",   glm::vec3(1.0f));

shader.setVec3("pointLight.position", glm::vec3(12.0f, 8.0f, 15.0f));
shader.setVec3("pointLight.ambient",  glm::vec3(0.05f));
shader.setVec3("pointLight.diffuse",  glm::vec3(0.8f));
shader.setVec3("pointLight.specular", glm::vec3(1.0f));
shader.setFloat("pointLight.constant",  1.0f);
shader.setFloat("pointLight.linear",    0.09f);
shader.setFloat("pointLight.quadratic", 0.032f);


        for (unsigned int i = 0; i < textures.size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name = textures[i].type;
            number = std::to_string(diffuseNr++); // only diffuse for now

            shader.setInt((name + number).c_str(), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
        