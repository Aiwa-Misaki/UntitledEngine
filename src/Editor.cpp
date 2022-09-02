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
    //加载一个游戏工程到内存中
    string workUrl="../resource/work";
    Json::Reader reader;
    Json::Value read_value;
    ifstream in(workUrl);
    stringstream buf;
    buf<<in.rdbuf();
    string str_json(buf.str());
    reader.parse(str_json, read_value);
    work= make_shared<Work>(read_value);
    cout<<"加载项目"<<work->name<<"成功"<<endl;
    in.close();
    //初始化渲染系统
    renderSystem= make_shared<RenderSystem>(work->curScene);
    cout<<"初始化渲染系统成功"<<endl;

    //初始化UI显示相关的变量
    editorUI->initEditorUIContext();
}

shared_ptr<Scene> Editor::getCurScene()
{
    return Editor::instance->work->curScene;
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