//
// Created by εθζ―δΈ on 2022/9/21.
//

#ifndef UNTITLEDENGINE_ENGINE_H
#define UNTITLEDENGINE_ENGINE_H
#include"json.h"
#include<iostream>
#include "Work.h"
#include"RuntimeResManager.h"
using namespace std;
class Engine {
public:
    static Engine *instance;
    static shared_ptr<Work>getCurWork()
    {
        return work;
    }

    static void init();
private:
    Engine();
    static shared_ptr<Work>work;

};


#endif //UNTITLEDENGINE_ENGINE_H
