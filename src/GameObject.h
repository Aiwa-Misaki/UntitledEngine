//
// Created by εθζ―δΈ on 2022/8/17.
//

#ifndef OPENGLTEST_GAMEOBJECT_H
#define OPENGLTEST_GAMEOBJECT_H

#include<string>
#include<unordered_map>
#include"Components/Transform.h"
#include"Components/Component.h"
#include"Components/MeshRenderer.h"
#include"Json.h"
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include <rttr/registration>
#include<rttr/instance.h>
#include"ComponentManager.h"


using namespace rttr;
using namespace std;
//class Engine;
class GameObject {
public:
    string name;
    string dir;//dir plus name must be unique. dir:like aaa/bbb/ccc/
    string parentFullDir;//full dir includes dir and name, like aaa/bbb/ccc/ddd
    shared_ptr<unordered_map<string,shared_ptr<Component>>> componentTable;
    explicit GameObject(Json::Value& );

    template<typename T>
    shared_ptr<T> getComponent()
    {
        type t=type::get<T>();
        for(auto iter=componentTable->begin();iter!=componentTable->end();iter++)
        {
            type t1=type::get(*(iter->second));
            if(t==t1)
            {
                shared_ptr<T> child_ptr= dynamic_pointer_cast<T>(iter->second);
                return child_ptr;
            }
        }
        return nullptr ;
    }
    
   int getLevel()
   {
       int num=0;
       for(int i=0;i<parentFullDir.size();i++)
       {
           if(parentFullDir[i]=='/')
               num++;
       }
       return num;
   }
   shared_ptr<GameObject> parent();
};


#endif //OPENGLTEST_GAMEOBJECT_H
