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
        ImGui::Text("XXX");
        //ImGui::SameLine();
        ImGui::Indent(); //另起一行制表符开始绘制Button
        ImGui::Button("2222", ImVec2(100, 50));

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