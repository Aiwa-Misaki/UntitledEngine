//
// Created by 克莉斯丁 on 2022/8/20.
//

#ifndef OPENGLTEST_RENDERSYSTEM_H
#define OPENGLTEST_RENDERSYSTEM_H

#include "../external/glad/glad.h"
#include "mesh.h"
#include <GLFW/glfw3.h>
#include"Scene.h"
#include"camera.h"
#include"GameObject.h"
#include"Components/MeshRenderer.h"
#include"Engine.h"
class Scene;
class RenderSystem {
public:
    bool renderMode=false;//false:编辑器模式 true:场景模式
    RenderSystem(shared_ptr<Scene> scene);
    void meshSubmit(shared_ptr<Mesh> mesh);
    void tick();

};


#endif //OPENGLTEST_RENDERSYSTEM_H
