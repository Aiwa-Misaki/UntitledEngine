//
// Created by 克莉斯丁 on 2022/8/20.
//

#ifndef OPENGLTEST_EDITORUI_H
#define OPENGLTEST_EDITORUI_H

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
class EditorUI {
public:
    EditorUI(GLFWwindow*);
    ~EditorUI();
    void tick();
};


#endif //OPENGLTEST_EDITORUI_H
