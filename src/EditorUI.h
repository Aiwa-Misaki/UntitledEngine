//
// Created by 克莉斯丁 on 2022/8/20.
//

#ifndef OPENGLTEST_EDITORUI_H
#define OPENGLTEST_EDITORUI_H

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"Editor.h"
#include"Editors/InspectorUI.h"
#include<unordered_map>
class Editor;
class EditorUI {
public:
    EditorUI(GLFWwindow*);
    ~EditorUI();
    void tick();
    //初始化一些显示UI需要用到的变量的值
    void initEditorUIContext();
    //物体列表中的某个物体菜单是否折叠 false：折叠 true：不折叠
    shared_ptr<unordered_map<string,bool>>gameObjectMenuShow;
};


#endif //OPENGLTEST_EDITORUI_H
