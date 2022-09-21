//
// Created by 克莉斯丁 on 2022/8/20.
//

#include "Editor.h"

Editor *Editor::instance=nullptr;
Editor::Editor() {
    //实现单例模式
    instance=this;
    //创建编辑器窗口
    editorWindow= make_shared<EditorWindow>();
    //创建编辑器UI系统
    editorUI= make_shared<EditorUI>(editorWindow->window);
    //创建引擎示例（这里尝试使用另一种单例模式）
    Engine::init();
    //初始化渲染系统
    renderSystem= make_shared<RenderSystem>(Engine::getCurWork()->curScene);
    cout<<"初始化渲染系统成功"<<endl;

    //初始化UI显示相关的变量
    editorUI->initEditorUIContext();
}

shared_ptr<Scene> Editor::getCurScene()
{
    return Engine::getCurWork()->curScene;
}
void Editor::run() const
{
    while (!glfwWindowShouldClose(editorWindow->window))
    {
        // per-frame time logic
        // --------------------
        /*
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        */
        // input
        // -----
        //processInput(window);

        // Start the Dear ImGui frame 启动IMgui Frame框架.
        editorUI->tick();
        // render
        // ------
        renderSystem->tick();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());





        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(editorWindow->window);
        glfwPollEvents();
    }


}