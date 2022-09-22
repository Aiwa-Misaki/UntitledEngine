//
// Created by 克莉斯丁 on 2022/9/22.
//

#ifndef UNTITLEDENGINE_MATERIAL_H
#define UNTITLEDENGINE_MATERIAL_H
#include"Asset.h"
#include"Json.h"
#include"shader.h"
#include"RuntimeResManager.h"
#include<iostream>
#include<unordered_map>
using namespace std;
class Material:public Asset {
public:
    string name;
    string shader_vs_path,shader_fs_path;
    shared_ptr<Shader>shader;
    shared_ptr<unordered_map<string,glm::vec3>>vec3Map;
    shared_ptr<unordered_map<string,glm::mat4>>mat4Map;
    explicit Material(string  url)
    {
        mat4Map= make_shared<unordered_map<string,glm::mat4>>();
        vec3Map= make_shared<unordered_map<string,glm::vec3>>();
        url="../resource/"+url;
        ifstream in(url);
        stringstream buf;
        buf<<in.rdbuf();
        string str_json(buf.str());
        Json::Reader reader;
        Json::Value read_value;
        reader.parse(str_json,read_value);
        int size=read_value.getMemberNames().size();
        for(int i=0;i<size;i++)
        {
            string key=read_value.getMemberNames()[i];
            if(key=="name")
            {
                this->name=read_value[key].asString();
            }
            else if(key=="shader_vs")
            {
                shader_vs_path=read_value[key].asString();

            }
            else if(key=="shader_fs")
            {
                shader_fs_path=read_value[key].asString();
            }
            else if(key=="params")
            {
                Json::Value paList=read_value[key];
                int paNum=paList.size();
                for(int j=0;j<paNum;j++)
                {
                    Json::Value pa=paList[j];
                    string paName=pa["name"].asString();
                    string paType=pa["type"].asString();
                    if(paType=="vec3")
                    {
                        if(pa.isMember("value"))
                            vec3Map->insert(pair<string,glm::vec3>(paName,glm::vec3(pa["value"][0].asFloat(),pa["value"][1].asFloat(),pa["value"][2].asFloat())));
                        else
                            vec3Map->insert(pair<string,glm::vec3>(paName,glm::vec3(1.0f,1.0f,1.0f)));
                    }
                    else if(paType=="mat4")
                    {
                        glm::mat4 mat=glm::mat4(1.0f);
                        mat4Map->insert(pair<string,glm::mat4>(paName,mat));
                    }
                }
            }
            //TODO:shadery也是一种资源，需要用resmanager管理
            this->shader=RuntimeResManager::getRes<Shader>("../resource/"+shader_vs_path);


        }
        in.close();
    }
};


#endif //UNTITLEDENGINE_MATERIAL_H
