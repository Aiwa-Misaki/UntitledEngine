//
// Created by 克莉斯丁 on 2022/9/15.
//

#include "FileManager.h"
FileManager* FileManager::instance= nullptr;
FileManager::FileManager() {
    instance=this;
    curPath=DEFAULT_WORK_PATH;
    curPath=fs::canonical(curPath);
    curFilesList.clear();
    for (const auto & entry : fs::directory_iterator(curPath))
    {
        string t= entry.path().filename();
        curFilesList.push_back(t);
    }




}
void FileManager::showFilesList()
{
    for(int i=0;i<curFilesList.size();i++)
    {
        bool isClick=ImGui::Button(curFilesList[i].c_str(),ImVec2(200,25));
        if(isClick)
        {
            if(fs::is_directory(curPath+"/"+curFilesList[i]))
                enterNextFolderBtn(curFilesList[i]);
        }
    }
}
string FileManager::getCurPath()
{
    return curPath;
}
 void FileManager::setCurPath(const string & newCurPath)
{
    curPath=newCurPath;
    curPath=fs::canonical(curPath);
    curFilesList.clear();
    if(curPath!=fs::canonical(DEFAULT_WORK_PATH))
    {
        curFilesList.push_back("../");
    }
    for (const auto & entry : fs::directory_iterator(curPath))
    {
        string t= entry.path().filename();
        curFilesList.push_back(t);
    }
}
void FileManager::enterNextFolderBtn(string nextFolder)
{
    string nextPath=curPath+"/"+nextFolder;
    setCurPath(nextPath);
}

void FileManager::executeCMD(const char *cmd, char *result)
{
    char buf_ps[1024];
    char ps[1024]={0};
    FILE *ptr;
    strcpy(ps, cmd);
    if((ptr=popen(ps, "r"))!=nullptr)
    {
        while(fgets(buf_ps, 1024, ptr)!= nullptr)
        {
            strcat(result, buf_ps);
            if(strlen(result)>1024)
                break;
        }
        pclose(ptr);
        ptr = nullptr;
    }
    else
    {
        printf("popen %s error", ps);
    }
}

