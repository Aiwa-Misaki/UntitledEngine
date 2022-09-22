//
// Created by 克莉斯丁 on 2022/9/21.
//

#ifndef UNTITLEDENGINE_RUNTIMERESMANAGER_H
#define UNTITLEDENGINE_RUNTIMERESMANAGER_H

#include<iostream>
#include<unordered_map>
#include <rttr/registration>
#include<rttr/instance.h>
#include"Asset.h"
#include"mesh.h"
using namespace rttr;
using namespace std;
class RuntimeResManager {
public:
    static shared_ptr<unordered_map<string,shared_ptr<Asset>>> assets;
    static RuntimeResManager *instance;
    static void init();

    //这里的T请传入指针类型
    template<typename T>
    static shared_ptr<T> getRes(string path){
        type t=type::get<T>();
        for(auto iter=assets->begin();iter!=assets->end();iter++)
        {
            type t1=type::get(*(iter->second));
            if(t==t1&&iter->first==path)//该资源已经保存过了，直接取出
            {
                shared_ptr<T> child_ptr= dynamic_pointer_cast<T>(iter->second);
                return child_ptr;
            }
        }
        shared_ptr<T>tt=make_shared<T>(path);
        assets->insert(pair<string,shared_ptr<T>>(path,tt));
        return tt;
    }
private:
    RuntimeResManager();

};


#endif //UNTITLEDENGINE_RUNTIMERESMANAGER_H
