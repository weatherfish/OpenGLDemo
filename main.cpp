
#include "glFramework/core.h"
#include "wrapper/checkError.h"
#include "applicaiton/application.h"
#include "glFramework/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "applicaiton/stb_image.h"

// 顶点数据
float vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0, 0.0, 0.0f, 0.0f, 1.0f,// 左下角
     0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0f, 1.0f, 0.0f,// 右下角
     0.5f,  0.5f, 0.0f, 1.0, 1.0, 1.0f, 0.0f, 0.0f,// 右上
     -0.5f, 0.5f, 0.0f, 0.0, 1.0, 1.0f, 1.0f, 0.0f, // 左上
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
 unsigned int texture;

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
    int width, height, channels;

    ///翻转y轴
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load("assets/textures/1.png", &width, &height, &channels, STBI_rgb_alpha);
    // unsigned char* data = stbi_load("assets/textures/2.jpg", &width, &height, &channels, STBI_rgb_alpha);

    //生成纹理
    glGenTextures(1, &texture);
    //激活纹理单元 0-15
    glActiveTexture(GL_TEXTURE0);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, texture);
    //传输纹理数据  同时会开辟显存
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //释放数据
    stbi_image_free(data);
    //设置纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //大于使用线性插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //小于取附近值

    //设置纹理包裹
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    shader->begin();
    shader->setFloat("time", glfwGetTime());
    shader->setFloat("speed", 2.0);

     shader->setInt("sampler", 0);

    // glFrontFace(GL_CW);
    // glCullFace(GL_CULL_FACE);
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_DEPTH_TEST);

    // glUniform4f(location, 0.2, 0.3f, 0.8f, 1.0f);
    // 绘制三角形
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

     shader->end();
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
    prepareTexture();

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

