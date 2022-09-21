//
// Created by 克莉斯丁 on 2022/9/21.
//

#include "Engine.h"

Engine *Engine::instance= nullptr;
shared_ptr<Work> Engine::work= nullptr;
Engine::Engine(){

}
void Engine::init()
{
    instance= new Engine();
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
}