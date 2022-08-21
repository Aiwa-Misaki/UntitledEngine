//
// Created by 克莉斯丁 on 2022/8/18.
//

#ifndef OPENGLTEST_TRANSFORM_H
#define OPENGLTEST_TRANSFORM_H
#include"Component.h"
#include <glm/glm.hpp>

using namespace glm;
struct Transform :public Component{
public:
RTTR_ENABLE(Component)
public:
    vec3 position;
    vec3 rotation;
    vec3 scale;
    Transform(){

    }
    virtual void debug()
    {
        cout<<"type:Transform"<<endl;
        cout<<"position:"<<position[0]<<" "<<position[1]<<" "<<position[2]<<endl;
    }
    virtual void setup(){};
};



#endif //OPENGLTEST_TRANSFORM_H
