//
// Created by 克莉斯丁 on 2022/8/19.
//

#include "Work.h"

Work::Work(string& name) {
    curScene= make_shared<Scene>();//create the first scene
    sceneList= make_shared<vector<string>>();
    string firstSceneUrl="/scenes/sampleScene";
    sceneList->push_back(firstSceneUrl);
    this->name=name;
}

Work::Work(Json::Value & jsonValue)
{


    sceneList=make_shared<vector<string>>();
    int size=jsonValue.getMemberNames().size();
    for(int i=0;i<size;i++)
    {
        string key=jsonValue.getMemberNames()[i];
        if(key=="name")
        {
            string value=jsonValue[key].asString();
        }
        else if(key=="sceneList")
        {
            int sceneNumber=jsonValue[key].size();
            for(int j=0;j<sceneNumber;j++)
            {
                string sceneUrl=jsonValue[key][j].asString();

                //TODO:根据场景的url实例化Scene类，保存引用到Work
                if(j==0)
                    curScene= make_shared<Scene>(sceneUrl);
                sceneList->push_back(sceneUrl);
            }
        }

    }

}