
#include "glFramework/core.h"
#include "wrapper/checkError.h"
#include "applicaiton/application.h"
#include "glFramework/Shader.h"
#include "glFramework/Texture.h"

// 顶点数据
float vertices[] = {
    -0.5f, -1.0f, 0.0f, 0.0, 0.0, 0.0f, 0.0f, 1.0f,// 左下角
     0.5f, -1.0f, 0.0f, 1.0, 0.0, 0.0f, 1.0f, 0.0f,// 右下角
     0.5f,  1.0f, 0.0f, 1.0, 1.0, 1.0f, 0.0f, 0.0f,// 右上
     -0.5f, 1.0f, 0.0f, 0.0, 1.0, 1.0f, 1.0f, 0.0f, // 左上
};

// 索引数据
unsigned int indices[] = {
    0, 1, 2, // 三角形的三个顶点索引
    2, 3, 0
};

void frameBufferSizeCallBack(int width, int height){
    std::cout<<" width = "<<width<<" height = "<<height<<std::endl;
}

void keyCallback(int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE){
        exit(0);
    }
}

Texture *texture =nullptr;
Texture *texture2 =nullptr;
Texture *texture3 =nullptr;
Shader *shader = nullptr;
unsigned int vao;
unsigned int vbo;
unsigned int ebo;
glm::mat4 transform(1.0f);
glm::mat4 viewMatrix(1.0f);

void prepare(){
 // 创建并绑定VAO
   
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 创建并绑定VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 创建并绑定EBO
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 配置顶点属性指针
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));

    glEnableVertexAttribArray(2);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5* sizeof(float)));
}

void  prepareTexture()
{
    std::string path = "assets/textures/1.png";
    std::string path2 = "assets/textures/1.jpg";
    std::string path3 = "assets/textures/2.jpg";
    texture = new Texture(path, 0);
    texture2 = new Texture(path2, 1);
    texture3 = new Texture(path3, 2);
}

void doRotation()
{
    // transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    // angle += 0.1f;
    float angle = 0.1f;

    // transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));//旋转

    ///先平移再旋转
    // transform = glm::translate(transform, glm::vec3(0.01f, 0.0f, 0.0f));//旋转
    // transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));//旋转

    ///先旋转再平移
    transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));//旋转
    transform = glm::translate(transform, glm::vec3(0.01f, 0.0f, 0.0f));//旋转
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    shader->begin();
    shader->setFloat("time", glfwGetTime());
    shader->setFloat("speed", 2.0);

    shader->setInt("sampler", 0);
    shader->setInt("sampler2", 1);
    shader->setInt("sampler3", 2);

    shader->setMatrix4x4("transform", transform);
    shader->setMatrix4x4("viewMatrix", viewMatrix);
    
    // doRotation();

    // glFrontFace(GL_CW);
    // glCullFace(GL_CULL_FACE);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);

    // glUniform4f(location, 0.2, 0.3f, 0.8f, 1.0f);
    // 绘制三角形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    shader->end();
}

void do_transform()
{
   glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //旋转 以原点为中心旋转
   glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));    //平移 
   glm::mat4 s1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.6f, 1.0f, 1.0f));    //缩放:将点变成原来的多少倍

   ///组合变换，先做的变换位于最右边。 先旋转，再平移
   transform = t1 * r1;
}

void prepareCamera(){
    ///生成一个viewMatrix, eye:当前摄像机所在位置， center：当前摄像机看向的点，up 穹顶向量用于定义摄像机的垂直方向
    viewMatrix = glm::lookAt(glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

int main()
{
    if( !app->init(400, 800)){
        return -1;
    }
    
    prepareCamera();

//     //设置监听
    app->setResizeCallback(frameBufferSizeCallBack);
    app-> setKeyCallback(keyCallback);
//     //设置刷新
    glfwSwapInterval(1);

    std::string basic_v = "assets/shader/basic_vertex.glsl";
    std::string basic_f = "assets/shader/basic_fragment.glsl";

    shader = new Shader(basic_v.c_str(), basic_f.c_str());

    shader->begin();

    prepare();
    prepareTexture();

    // do_transform();

     // 渲染循环
    while (app->update())
    {  
        render();
    }

    // 清理资源
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);

    app->destory();
    delete texture;

    return 0;

}

