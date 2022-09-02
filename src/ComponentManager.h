//
// Created by 克莉斯丁 on 2022/8/19.
//

#ifndef OPENGLTEST_COMPONENTMANAGER_H
#define OPENGLTEST_COMPONENTMANAGER_H

#include"Components/Component.h"
#include"mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ComponentManager {

public :
    static const type int_type,vec3_type,str_type;
    static const type mesh_type,mesh_ptr_type;
    static const void deserialize(Json::Value &json,instance &ins,type &t)
    {
        int propertyNum=json.getMemberNames().size();
        for(int i=0;i<propertyNum;i++)
        {
            string key=json.getMemberNames()[i];
            Json::Value value=json[key];
            type pt=t.get_property(key).get_type();
            property pro=t.get_property(key);
            bool outcome;
            if(pt==int_type)
            {

                outcome=pro.set_value(ins,value.asInt());
            }
            else if(pt==vec3_type)
            {

                outcome=pro.set_value(ins,glm::vec3(value[0].asFloat(),value[1].asFloat(),value[2].asFloat()));
            }
            else if(pt==str_type)
            {
                outcome=pro.set_value(ins,value.asString());
            }
            else if(pt==mesh_type)
            {
                string meshUrl=value.asString();
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
                    for(int j=0;j<aimesh->mNumFaces;j++)
                    {
                        for(int k=0;k<aimesh->mFaces[j].mNumIndices;k++)
                        {
                            indices.push_back(aimesh->mFaces[j].mIndices[k]);
                        }
                    }
                    //cout<<"indices.size:"<<indices.size()<<endl;
                    vector<Texture>textures;
                    shared_ptr<Mesh> mesh= make_shared<Mesh>();
                    mesh->url=meshUrl;
                    //cout<<"w"<<endl;
                    mesh->setupMesh(vertices,indices,textures);
                    //cout<<"verts:"<<mesh->vertices.size()<<endl;
                    pro.set_value(ins, mesh);
                }

            }
        }
    }
    static const string getValueStr(variant &prop_value,type &prop_type)
    {
        if(prop_type==int_type)
            return prop_value.to_string();
        if(prop_type==str_type)
            return prop_value.to_string();
        if(prop_type==mesh_type)
        {
            return prop_value.get_value<shared_ptr<Mesh>>()->url;
        }
        return "";
    }

};

#endif //OPENGLTEST_COMPONENTMANAGER_H
