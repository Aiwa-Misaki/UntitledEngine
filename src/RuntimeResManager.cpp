//
// Created by 克莉斯丁 on 2022/9/21.
//

#include "RuntimeResManager.h"

shared_ptr<unordered_map<string,shared_ptr<Asset>>> RuntimeResManager::assets=nullptr;
RuntimeResManager *RuntimeResManager::instance= nullptr;
RuntimeResManager::RuntimeResManager() {

}

void RuntimeResManager::init()
{
    instance=new RuntimeResManager();
    assets= make_shared<unordered_map<string,shared_ptr<Asset>>>();

}
/*
template<typename T>
T RuntimeResManager::getRes(string path){
    type t=type::get<T>();
    //资源是网格类型
    if(t==type::get<shared_ptr<Mesh>>())
    {
        shared_ptr<Mesh> tm= make_shared<Mesh>(path);
        meshMap->insert(pair<string,shared_ptr<Mesh>>(path,tm));
        return tm;
    }
}*/