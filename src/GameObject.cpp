//
// Created by 克莉斯丁 on 2022/8/17.
//

#include "GameObject.h"

GameObject::GameObject(Json::Value &json)
{


    string objectName=json["name"].asString();
    if(objectName.find('/')>objectName.size()||objectName.find('/')<0)//this object is at top level
    {
        this->parentFullDir=objectName;
        this->name=objectName;
        this->dir="";
    }
    else{
        this->name=objectName.substr(objectName.find_last_of('/')+1,-1);
        this->parentFullDir=objectName;
        this->dir=json["name"].asString().substr(0,objectName.find_last_of('/')+1);
    }

    componentTable= make_shared<unordered_map<string,shared_ptr<Component>>>();
    int componentNum=json["components"].size();
    for(int i=0;i<componentNum;i++)
    {
        Json::Value componentJson=json["components"][i];
        string componentName=componentJson["name"].asString();
        shared_ptr<Component> c;
        type t=type::get_by_name(componentName);
        if(componentName=="Transform")
        {
            c= make_shared<Transform>();

        }
        else if(componentName=="MeshRenderer")
        {
            c= make_shared<MeshRenderer>();
        }
        instance c_ins=*c;
        ComponentManager::deserialize(componentJson["values"],c_ins,t);
        componentTable->insert(make_pair(componentName,c));
        //componentTable->at(componentName)->debug();



    }
    //getComponent<Transform>();

}

shared_ptr<GameObject> GameObject::parent()
{
    string tempDir=dir;
    tempDir.pop_back();
    return Editor::instance->work->curScene->gameObjectList->at(tempDir);
}