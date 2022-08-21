//
// Created by 克莉斯丁 on 2022/8/17.
//

#ifndef OPENGLTEST_SCENE_H
#define OPENGLTEST_SCENE_H
#include<unordered_map>
#include<string>
#include<fstream>
#include"GameObject.h"
#include"Json.h"
#include<iostream>
using namespace std;
class Scene {
public:
    string name;
    shared_ptr<unordered_map<string,shared_ptr<GameObject>>>gameObjectList;
    shared_ptr<vector<string>>gameObjectNameList;
    Scene()
    {

    }
    Scene(string&);
};


#endif //OPENGLTEST_SCENE_H
