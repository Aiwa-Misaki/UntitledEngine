//
// Created by 克莉斯丁 on 2022/8/17.
//

#include "Scene.h"

Scene::Scene(string& url)
{
    url="../resource/"+url;
    ifstream in(url);
    //cout<<url<<endl;
    stringstream buf;
    buf<<in.rdbuf();
    string str_json(buf.str());
    Json::Reader reader;
    Json::Value read_value;
    reader.parse(str_json,read_value);
    int size=read_value.getMemberNames().size();
    for(int i=0;i<size;i++)
    {
        string key=read_value.getMemberNames()[i];
       if(key=="name")
       {
           this->name=read_value[key].asString();
       }
       else if(key=="gameObjectList")
       {
           gameObjectList= make_shared<unordered_map<string,shared_ptr<GameObject>>>();
           gameObjectNameList= make_shared<vector<string>>();
           Json::Value gameObjectListJson=read_value[key];
           int gameObjectNum=gameObjectListJson.size();
           for(int j=0;j<gameObjectNum;j++) {
               Json::Value gameObjectJson = gameObjectListJson[j];
               string gameObjectName = gameObjectJson["name"].asString();
               gameObjectNameList->push_back(gameObjectName);
               shared_ptr<GameObject> tempGameObject = make_shared<GameObject>(gameObjectJson);
               gameObjectList->insert(make_pair(gameObjectName, tempGameObject));
               //TODO：让GameObject自己想办法解析自己的Json文件
           }
       }


    }
    in.close();
}
