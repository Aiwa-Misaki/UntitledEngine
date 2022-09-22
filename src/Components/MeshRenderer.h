//
// Created by 克莉斯丁 on 2022/8/18.
//

#ifndef OPENGLTEST_MESHRENDERER_H
#define OPENGLTEST_MESHRENDERER_H

#include"Component.h"
#include"../Material.h"
#include"../mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
using namespace std;
class MeshRenderer:public Component {
RTTR_ENABLE(Component)
public:
    shared_ptr<Mesh> mesh;
    shared_ptr<Material>material;
    MeshRenderer(){
        //mesh=make_shared<Mesh>();
    }
    virtual void setup();
    virtual void debug()
    {
        cout<<mesh->vertices.size()<<endl;
    }
};


#endif //OPENGLTEST_MESHRENDERER_H
