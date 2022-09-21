//
// Created by 克莉斯丁 on 2022/8/11.
//

#ifndef OPENGLTEST_MESH_H
#define OPENGLTEST_MESH_H

#include<glm/glm.hpp>
#include<iostream>
#include <utility>
#include<vector>
#include "shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

struct Vertex {
public:glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
    Texture()
    {

    }
};
class Mesh {
public:
    string url;
    /*  网格数据  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    /*  函数  */
    //Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader shader);
public:
    /*  渲染数据  */
    unsigned int VAO{}, VBO{}, EBO{};
    /*  函数  */
    //void setupMesh();

    Mesh()= default;

    Mesh(string path){
        const string& meshUrl=path;
        //加载mesh资源部分
        {
            Assimp::Importer importer;
            const aiScene* scene=importer.ReadFile("../resource/"+meshUrl,   aiProcess_CalcTangentSpace       |
                                                                             aiProcess_Triangulate            );

            // If the import failed, report it
            if( !scene)
            {
                cout<<"加载模型"<<meshUrl<<"失败"<<endl;
                return;
            }
            aiMesh* aimesh=scene->mMeshes[0];
            vector<Vertex> vertices(aimesh->mNumVertices);
            for(int j=0;j<aimesh->mNumVertices;j++)
            {
                vertices[j].Position[0]=aimesh->mVertices[j][0];
                vertices[j].Position[1]=aimesh->mVertices[j][1];
                vertices[j].Position[2]=aimesh->mVertices[j][2];

                vertices[j].Normal[0]=aimesh->mNormals[j][0];
                vertices[j].Normal[1]=aimesh->mNormals[j][1];
                vertices[j].Normal[2]=aimesh->mNormals[j][2];

                vertices[j].TexCoords[0]=aimesh->mTextureCoords[0][j][0];
                vertices[j].TexCoords[1]=aimesh->mTextureCoords[0][j][1];
            }
            //cout<<"vertices.size"<<vertices.size()<<endl;
            vector<unsigned int> indices;
            for(int j=0;j<aimesh->mNumFaces;j++) {
                for (int k = 0; k < aimesh->mFaces[j].mNumIndices; k++) {
                    indices.push_back(aimesh->mFaces[j].mIndices[k]);
                }
            }
            vector<Texture>textures;
            //shared_ptr<Mesh> mesh= make_shared<Mesh>();
            this->url=meshUrl;
            this->setupMesh(vertices,indices,textures);
            //pro.set_value(ins, mesh);
        }
    }

    ~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1,&EBO);
    }
private:
    void setupMesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = std::move(vertices);
        this->indices = std::move(indices);
        this->textures = std::move(textures);
        /*
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                     &indices[0], GL_STATIC_DRAW);

        // 顶点位置
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // 顶点法线
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // 顶点纹理坐标
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
         */
    }


};

#endif //OPENGLTEST_MESH_H
