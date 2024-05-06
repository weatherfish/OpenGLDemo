
#include "glFramework/core.h"
#include "wrapper/checkError.h"
#include "applicaiton/application.h"
#include "glFramework/Shader.h"

// 顶点数据
float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// 左下角
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// 右下角
     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// 右上
     -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, // 左上
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


 Shader *shader = nullptr;
 unsigned int vao;
 unsigned int vbo;
 unsigned int ebo;

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6* sizeof(float), (void*)(3* sizeof(float)));
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    shader->begin();
    shader->setFloat("time", glfwGetTime());
    shader->setFloat("speed", 2.0);

    // glFrontFace(GL_CW);
    // glCullFace(GL_CULL_FACE);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);

    // glUniform4f(location, 0.2, 0.3f, 0.8f, 1.0f);
    // 绘制三角形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main()
{
  
    if( !app->init(800, 600)){
        return -1;
    }

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

    return 0;

}

