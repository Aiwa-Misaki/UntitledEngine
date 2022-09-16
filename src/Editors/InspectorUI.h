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
#include <rttr/registration>
#include<rttr/instance.h>
#include"../ComponentManager.h"

using namespace std;
class InspectorUI {
public:
    static void showComponentList(shared_ptr<GameObject> gameObject){
        for(auto iter=gameObject->componentTable->begin();iter!=gameObject->componentTable->end();iter++)
        {
            ImGui::Button(iter->first.c_str(),ImVec2(100,25));
            auto com=iter->second;
            type t=com->get_type();
            instance ins=*com;
            for (auto& prop : t.get_properties())
            {
                ImGui::Button(prop.get_name().data(),ImVec2(80,20));
                auto prop_value=prop.get_value(ins);
                auto prop_type=prop.get_type();
                string valueStr=ComponentManager::getValueStr(prop_value,prop_type);
                ImGui::Text(valueStr.c_str());

            
            }
        }
    }
    static string chooseGameObjectName;
};



#endif //UNTITLEDENGINE_INSPECTORUI_H
