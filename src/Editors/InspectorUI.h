//
// Created by 克莉斯丁 on 2022/9/2.
//

#ifndef UNTITLEDENGINE_INSPECTORUI_H
#define UNTITLEDENGINE_INSPECTORUI_H

#include"../GameObject.h"
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include<iostream>
using namespace std;
class InspectorUI {
public:
    static void showComponentList(shared_ptr<GameObject> gameObject){
        for(auto iter=gameObject->componentTable->begin();iter!=gameObject->componentTable->end();iter++)
        {
            ImGui::Button(iter->first.c_str(),ImVec2(100,20));
        }
    }
    static string chooseGameObjectName;
};



#endif //UNTITLEDENGINE_INSPECTORUI_H
