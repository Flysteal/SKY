#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stb_image.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::Draw(Shader& shader) {
    for (auto& mesh : meshes)
        mesh.Draw(shader);
}

void Model::loadModel(const std::string& path) {
    Assimp::Importer importer;

const aiScene* scene = importer.ReadFile(path,
    aiProcess_Triangulate |
    aiProcess_FlipUVs |
    aiProcess_CalcTangentSpace |
    aiProcess_GenNormals);

if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
    return;
}

// Now you can safely check vertex colors in meshes during processing.



    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.Position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal   = glm::vec3(mesh->mNormals[i].x,  mesh->mNormals[i].y,  mesh->mNormals[i].z);
        vertex.TexCoords = mesh->mTextureCoords[0] ?
            glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) :
            glm::vec2(0.0f);

        if (mesh->HasVertexColors(0)) {
            vertex.Color = glm::vec3(
                mesh->mColors[0][i].r,
                mesh->mColors[0][i].g,
                mesh->mColors[0][i].b
            );
        } else {
            // No vertex color – check material diffuse color
            glm::vec3 fallbackColor(1.0f, 0.0f, 0.0f); // default to red
            if (mesh->mMaterialIndex >= 0) {
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                aiColor3D color(0.f, 0.f, 0.f);
                if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
                    fallbackColor = glm::vec3(color.r, color.g, color.b);
                }
            }
            vertex.Color = fallbackColor;
        }


        vertices.push_back(vertex);
    }


    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        auto diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }


    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string texPath = str.C_Str();

        bool skip = false;
        for (auto& t : textures_loaded) {
            if (t.path == texPath) {
                textures.push_back(t);
                skip = true;
                break;
            }
        }

        if (!skip) {
            Texture texture;
            texture.id = TextureFromFile(texPath.c_str(), directory);
            texture.type = typeName;
            texture.path = texPath;
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory) {
    std::string filename = directory + "/" + std::string(path);
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = (nrComponents == 1) ? GL_RED :
                        (nrComponents == 3) ? GL_RGB : GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        std::cerr << "Texture failed to load: " << filename << "\n";
        stbi_image_free(data);
    }

    return textureID;
}

void Model::Translate(glm::vec3 vec)
{
    Matrix = glm::translate(Matrix, vec);
}