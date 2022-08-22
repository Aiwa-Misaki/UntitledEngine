//
// Created by 克莉斯丁 on 2022/8/19.
//

#ifndef OPENGLTEST_WORK_H
#define OPENGLTEST_WORK_H
#include"Scene.h"
#include<vector>
#include<iostream>
#include"json.h"
using namespace std;
class Scene;
class Work {
public:
    string name;
    shared_ptr<vector<string>> sceneList;
    shared_ptr<Scene> curScene;
    Work(Json::Value &);//从json中加载现有工程
    Work(string&);//创建新工程
};



#endif //OPENGLTEST_WORK_H
