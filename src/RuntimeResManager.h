//
// Created by 克莉斯丁 on 2022/9/21.
//

#ifndef UNTITLEDENGINE_RUNTIMERESMANAGER_H
#define UNTITLEDENGINE_RUNTIMERESMANAGER_H

#include<iostream>
#include<unordered_map>
#include <rttr/registration>
#include<rttr/instance.h>

#include"mesh.h"
using namespace rttr;
using namespace std;
class RuntimeResManager {
public:
    static RuntimeResManager *instance;
    static void init();

    //这里的T请传入指针类型
    template<typename T>
    static T getRes(string path){
        type t=type::get<T>();
        //资源是网格类型
        if(t==type::get<shared_ptr<Mesh>>())
        {
            shared_ptr<Mesh> tm= make_shared<Mesh>(path);
            meshMap->insert(pair<string,shared_ptr<Mesh>>(path,tm));
            return tm;
        }
    }
private:
    static shared_ptr<unordered_map<string,shared_ptr<Mesh>>>meshMap;
    RuntimeResManager();

};


#endif //UNTITLEDENGINE_RUNTIMERESMANAGER_H
