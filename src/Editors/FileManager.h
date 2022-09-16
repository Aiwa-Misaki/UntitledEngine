//
// Created by 克莉斯丁 on 2022/9/15.
//

#ifndef UNTITLEDENGINE_FILEMANAGER_H
#define UNTITLEDENGINE_FILEMANAGER_H

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include<iostream>
#include"../PublicItem.h"
#include<filesystem>
#include<vector>
#include <string>
#include <fstream>
using namespace std;
namespace fs = std::__fs::filesystem;
class FileManager {
public:
    static FileManager* instance;
    string getCurPath();
    void setCurPath(const string & newCurPath);
    FileManager();

    void showFilesList();
private:
    string curPath;
    void enterNextFolderBtn(string);
    vector<string>curFilesList;
    void executeCMD(const char *cmd, char *result);
};


#endif //UNTITLEDENGINE_FILEMANAGER_H
