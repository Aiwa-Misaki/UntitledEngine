//
// Created by 克莉斯丁 on 2022/8/20.
//

#include "RenderSystem.h"

RenderSystem::RenderSystem(shared_ptr<Scene> scene) :
lightingShader("../2.2.basic_lighting.vs", "../2.2.basic_lighting.fs"),
lightCubeShader("../2.2.light_cube.vs", "../2.2.light_cube.fs"){

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    //lightingShader=Shader("../2.2.basic_lighting.vs", "../2.2.basic_lighting.fs");

    //lightCubeShader=Shader("../2.2.light_cube.vs", "../2.2.light_cube.fs");
    for (auto iter=scene->gameObjectNameList->begin();iter!=scene->gameObjectNameList->end();iter++)
    {
        string key=*iter;
        auto obj=scene->gameObjectList->at(key);
        auto mr=obj->getComponent<MeshRenderer>();
        meshSubmit(mr->mesh);
    }

}

void RenderSystem::meshSubmit(shared_ptr<Mesh> mesh) {
    glGenVertexArrays(1, &(mesh->VAO));
    glGenBuffers(1, &(mesh->VBO));
    glGenBuffers(1, &(mesh->EBO));

    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), &(mesh->vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int),
                 &(mesh->indices[0]), GL_STATIC_DRAW);

    // 顶点位置
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // 顶点法线
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // 顶点纹理坐标
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);


}

void RenderSystem::tick()
{
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glViewport(560,530,1920*0.9,1080*0.9);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    lightingShader.use();
    lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setVec3("lightPos", lightPos);
    lightingShader.setVec3("viewPos", camera.Position);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)1920 / (float)1080, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    lightingShader.setMat4("projection", projection);
    lightingShader.setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    lightingShader.setMat4("model", model);

    // render the cube
    //glBindVertexArray(cubeVAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);


    for(auto i=Editor::instance->work->curScene->gameObjectNameList->begin();
    i!=Editor::instance->work->curScene->gameObjectNameList->end();i++)
    {
        string key=*i;
        auto obj=Editor::instance->work->curScene->gameObjectList->at(key);
        auto mr=obj->getComponent<MeshRenderer>();
        glm::mat4 model = glm::mat4(1.0f);
        model=glm::scale(model,obj->getComponent<Transform>()->scale);
        model=glm::rotate(model,glm::radians(obj->getComponent<Transform>()->rotation[0]),
                          glm::vec3(1,0,0));
        model=glm::rotate(model,glm::radians(obj->getComponent<Transform>()->rotation[1]),
                          glm::vec3(0,1,0));
        model=glm::rotate(model,glm::radians(obj->getComponent<Transform>()->rotation[2]),
                          glm::vec3(0,0,1));
        model=glm::translate(model,obj->getComponent<Transform>()->position);

        lightingShader.setMat4("model", model);
        //渲染这个物体的mesh
        glBindVertexArray(mr->mesh->VAO);
        glDrawArrays(GL_TRIANGLES,0,mr->mesh->indices.size());
    }



    /*
    // also draw the lamp object
    lightCubeShader.use();
    lightCubeShader.setMat4("projection", projection);
    lightCubeShader.setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightCubeShader.setMat4("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
     */
}