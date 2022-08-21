//
// Created by 克莉斯丁 on 2022/8/20.
//

#ifndef OPENGLTEST_EDITOR_H
#define OPENGLTEST_EDITOR_H

#include"EditorWindow.h"
#include "EditorUI.h"
#include"RenderSystem.h"
#include"Work.h"
class RenderSystem;
class Editor {
public:
    shared_ptr<EditorWindow>editorWindow;
    shared_ptr<EditorUI>editorUI;
    shared_ptr<RenderSystem>renderSystem;
    shared_ptr<Work>work;
    Editor();
    void run() const;
    static Editor* instance;

};


#endif //OPENGLTEST_EDITOR_H