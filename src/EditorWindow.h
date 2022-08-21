//
// Created by 克莉斯丁 on 2022/8/20.
//

#ifndef OPENGLTEST_EDITORWINDOW_H
#define OPENGLTEST_EDITORWINDOW_H

#include <GLFW/glfw3.h>
#include<iostream>
#include "../external/glad/glad.h"
using namespace std;
class EditorWindow {

public:
    EditorWindow();
    ~EditorWindow();
    GLFWwindow *window;
private:
    const unsigned int SCR_WIDTH = 1920;
    const unsigned int SCR_HEIGHT = 1080;
};


#endif //OPENGLTEST_EDITORWINDOW_H
