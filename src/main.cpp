#include "../external/glad/glad.h"
#include <GLFW/glfw3.h>
#include"camera.h"
#include "shader.h"
#include "mesh.h"
#include <iostream>
#include<fstream>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"Editor.h"

#include"json.h"
#include"Work.h"

#include <rttr/registration>
using namespace rttr;

struct MyStruct { MyStruct() {}; void func(double) {}; int data; };

RTTR_REGISTRATION
{
registration::class_<MyStruct>("MyStruct")
.constructor<>()
.property("data", &MyStruct::data)
.method("func", &MyStruct::func);

    registration::class_<Transform>("Transform")
            .constructor<>()
            .property("position", &Transform::position)
            .property("rotation", &Transform::rotation)
            .property("scale", &Transform::scale);

    registration::class_<Component>("Component")
            .constructor<>()
            .method("deserialize", &Component::deserialize);

    registration::class_<MeshRenderer>("MeshRenderer")
            .constructor<>()
            .property("mesh",&MeshRenderer::mesh);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);



using namespace std;

int main()
{

    shared_ptr<Editor> editor= make_shared<Editor>();
    editor->run();

    /*
    type t = type::get<MyStruct>();
    for (auto& prop : t.get_properties())
        std::cout << "name: " << prop.get_name() << std::endl;

    for (auto& meth : t.get_methods())
        std::cout << "name: " << meth.get_name() << std::endl;
    //json解析库测试
    Json::Value write_value;
    write_value["id"] = 123;
    write_value["name"] = "James";
    string str_json = write_value.toStyledString();

    Json::Reader reader;
    Json::Value read_value;

    if (reader.parse(str_json, read_value))
    {
        if (!read_value["id"].isNull())
        {
            cout<<"size:"<<read_value.size()<<endl;
            for(int i=0;i<read_value.size();i++)
            {
                cout<<read_value[read_value.getMemberNames()[i]]<<endl;

            }
            cout << read_value["id"].asInt() << endl;
            cout << read_value["name"].asString() << endl;
        }
    }
     */
    /*
    string workUrl="../res/work";
    Json::Reader reader;
    Json::Value read_value;
    ifstream in(workUrl);
    stringstream buf;
    buf<<in.rdbuf();
    string str_json(buf.str());
    reader.parse(str_json, read_value);

    shared_ptr<Work> work= make_shared<Work>(read_value);
    cout<<"加载"<<work->name<<"成功"<<endl;
    in.close();
     */

/*

#pragma region glfw,glad初始化
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();


    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
#pragma endregion

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("../2.2.basic_lighting.vs", "../2.2.basic_lighting.fs");
    Shader lightCubeShader("../2.2.light_cube.vs", "../2.2.light_cube.fs");

    Assimp::Importer importer;
    const aiScene* scene=importer.ReadFile("../monkey.obj",   aiProcess_CalcTangentSpace       |
                                                        aiProcess_Triangulate            );

    // If the import failed, report it
    if( !scene)
    {
        cout<<"No!!!!";
        //DoTheErrorLogging( importer.GetErrorString());
        //return false;
    }
    aiMesh* aimesh=scene->mMeshes[0];
    printf("%s",aimesh->mName.C_Str());
    vector<Vertex> vertices1(aimesh->mNumVertices);
    for(int i=0;i<aimesh->mNumVertices;i++)
    {
        vertices1[i].Position[0]=aimesh->mVertices[i][0];
        vertices1[i].Position[1]=aimesh->mVertices[i][1];
        vertices1[i].Position[2]=aimesh->mVertices[i][2];

        vertices1[i].Normal[0]=aimesh->mNormals[i][0];
        vertices1[i].Normal[1]=aimesh->mNormals[i][1];
        vertices1[i].Normal[2]=aimesh->mNormals[i][2];

        vertices1[i].TexCoords[0]=aimesh->mTextureCoords[0][i][0];
        vertices1[i].TexCoords[1]=aimesh->mTextureCoords[0][i][1];

    }
    vector<unsigned int> indices;
    for(int i=0;i<aimesh->mNumFaces;i++)
    {
        for(int j=0;j<aimesh->mFaces[i].mNumIndices;j++)
        {
            indices.push_back(aimesh->mFaces[i].mIndices[j]);
        }
    }
    vector<Texture>textures;
    Mesh *mesh=new Mesh(vertices1,indices,textures);


    //Mesh *mesh=new Mesh()
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    //创建VAO
    glGenVertexArrays(1, &cubeVAO);
    //创建VBO
    glGenBuffers(1, &VBO);

    //绑定VBO到GL_ARRAY_BUFFER目标上，之后对GL_ARRAY_BUFFER的操作都会用来配置VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //绑定VAO（在绑定VAO之后再执行绑定VBO的操作）
    glBindVertexArray(cubeVAO);

    // position attribute
    //解释一条顶点的属性（如位置，法线）的初始位置，数据类型，数据长度等等
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    //启用顶点属性（默认是禁用的）
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Start the Dear ImGui frame 启动IMgui Frame框架.
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

        // render
        // ------
        glViewport(560,530,SCR_WIDTH*0.9,SCR_HEIGHT*0.9);
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        lightingShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("lightPos", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // render the cube
        //glBindVertexArray(cubeVAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(mesh->VAO);
        glDrawArrays(GL_TRIANGLES,0,mesh->indices.size());


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

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());





        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    delete mesh;
    return 0;
    */

}




// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width/2, height/2);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}