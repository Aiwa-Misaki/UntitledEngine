//
// Created by 克莉斯丁 on 2022/8/18.
//

#ifndef OPENGLTEST_COMPONENT_H
#define OPENGLTEST_COMPONENT_H
#include<string>
#include<unordered_map>
#include"json.h"
#include"value.h"
#include<iostream>
#include<rttr/registration>
#include<rttr/instance.h>

using namespace rttr;
using namespace std;

class Component {
public:
    RTTR_ENABLE()
public:
    Component(){

    }
    void deserialize(Json::Value &);
    virtual void debug(){};
    virtual void setup(){};
};



#endif //OPENGLTEST_COMPONENT_H
