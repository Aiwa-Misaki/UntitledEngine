//
// Created by 克莉斯丁 on 2022/8/20.
//

#include "EditorUI.h"

EditorUI::EditorUI(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();


    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void EditorUI::initEditorUIContext() {
    //初始化物体列表显示与否（一开始全都显示）
    int gameObjectNum=Editor::instance->work->curScene->gameObjectNameList->size();
    gameObjectMenuShow= make_shared<unordered_map<string,bool>>();
    for(int i=0;i<gameObjectNum;i++)
        gameObjectMenuShow->insert(make_pair(Editor::instance->work->curScene->gameObjectNameList->at(i),true));
}

EditorUI::~EditorUI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void EditorUI::tick()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    {
        //开始绘制ImGui

        ImGui::Begin("Scene");
        ImGui::SetWindowPos("Scene",ImVec2(10,10));
        ImGui::SetWindowSize("Scene",ImVec2(250,500));// Create a window called "Hello, world!" and append into it.
        //ImGui::Text("XXX");
        //ImGui::SameLine();
        //ImGui::Indent(); //另起一行制表符开始绘制Button
        //ImGui::Button("2222", ImVec2(100, 50));

        //绘制场景中的物体列表，部分折叠


        {
            int index=0;
            for(auto iter=Editor::instance->work->curScene->gameObjectNameList->begin();
                iter!=Editor::instance->work->curScene->gameObjectNameList->end();iter++)
            {
                string key=*iter;

                auto obj=Editor::instance->work->curScene->gameObjectList->at(key);
                string name=obj->name;
                int level=obj->getLevel();
                bool isShow=true;
                auto tempObj=obj;
                while(true)
                {
                    if(tempObj->getLevel()==0)
                        break;
                    shared_ptr<GameObject> parent=tempObj->parent();
                    bool isShow1=gameObjectMenuShow->at(parent->parentFullDir);
                    if(isShow1==false)
                    {
                        isShow=false;
                        break;
                    }
                    tempObj=parent;
                }

                if(isShow)
                {
                    ImGui::SetCursorPos(ImVec2(10+level*15,20+index*25));
                    bool isClick=ImGui::Button(name.c_str(),ImVec2(100,20));
                    if(isClick)
                    {
                        if(gameObjectMenuShow->at(key)==false)
                            gameObjectMenuShow->at(key)=true;
                        else
                            gameObjectMenuShow->at(key)=false;
                    }
                    index++;
                }
        }



            //ImGui::SetWindowPos(name.c_str(),ImVec2(10+level*10,20+i*20));


        }

        ImGui::End();

        ImGui::Begin("Inspector");
        ImGui::SetWindowPos("Inspector",ImVec2(1150,10));
        ImGui::SetWindowSize("Inspector",ImVec2(250,500));
        ImGui::End();

        ImGui::Begin("Files");
        ImGui::SetWindowPos("Files",ImVec2(10,530));
        ImGui::SetWindowSize("Files",ImVec2(1400,220));
        ImGui::End();
    }

    // 3. Show another simple window.

    // Rendering
    ImGui::Render();

}