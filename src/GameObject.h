//
// Created by 克莉斯丁 on 2022/8/17.
//

#ifndef OPENGLTEST_GAMEOBJECT_H
#define OPENGLTEST_GAMEOBJECT_H

#include<string>
#include<unordered_map>
#include"Components/Transform.h"
#include"Components/Component.h"
#include"Json.h"
#include"stdlib.h"
#include"stdio.h"
#include<iostream>
#include <rttr/registration>
#include<rttr/instance.h>
#include"ComponentManager.h"
#include"Components/MeshRenderer.h"
using namespace rttr;
using namespace std;
class GameObject {
public:
    string name;
    string dir;//dir plus name must be unique. dir:like aaa/bbb/ccc/
    string parentFullDir;//full dir includes dir and name, like aaa/bbb/ccc/ddd
    shared_ptr<unordered_map<string,shared_ptr<Component>>> componentTable;
    GameObject(Json::Value& );

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
    }
};


#endif //OPENGLTEST_GAMEOBJECT_H
