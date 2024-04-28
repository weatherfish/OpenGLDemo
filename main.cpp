#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include "wrapper/checkError.h"
#include "applicaiton/application.h"

struct ShaderProgremSource{
    std::string VertexSource;
    std::string FragSource;
};

static ShaderProgremSource parseShader(const std::string file)
{
    std::ifstream stream(file);
    std::string line;

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    ShaderType type = ShaderType::NONE;

    std::stringstream ss[2];
    while (getline(stream, line))
    {   
        if(line.find("#shader") != std::string::npos){
             if(line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
             }
            else if (line.find("fragment") != std::string::npos)
             {
                type = ShaderType::FRAGMENT;
             }
        }else{
            ss[(int)type] <<line<<'\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
    
}

static unsigned int CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"Failed to compile "<<(type == GL_VERTEX_SHADER? "vertex" : "fragment") <<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
    unsigned int program =  glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// 顶点数据
float vertices[] = {
    -0.5f, -0.5f, 0.0f, // 左下角
     0.5f, -0.5f, 0.0f, // 右下角
     0.5f,  0.5f, 0.0f, // 右上
     -0.5f,  0.5f, 0.0f  // 左上
};

// 索引数据
unsigned int indices[] = {
    0, 1, 2, // 三角形的三个顶点索引
    2, 3, 0
};

void frameBufferSizeCallBack(GLFWwindow *window, int width, int height){
    std::cout<<" width = "<<width<<" height = "<<height<<std::endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE){
        exit(0);
    }
}


int main()
{
  
    if( !app->init(800, 600)){
        return -1;
    }

//     //设置监听
//     glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
//     glfwSetKeyCallback(window, keyCallback);
//     //设置刷新
//     glfwSwapInterval(1);

    // 创建并绑定VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 创建并绑定VBO
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 创建并绑定EBO
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 配置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    ShaderProgremSource source = parseShader("res/shader/basic.glsl");

    unsigned int progrem = CreateShader(source.VertexSource, source.FragSource);
    glUseProgram(progrem);

    int location = glGetUniformLocation(progrem, "u_Color");

    float r = 0.0f;
    float increment = 0.05f;

     // 渲染循环
    while (app->update())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // GLCall(glClear(-1));
        
        // glFrontFace(GL_CW);
        // glCullFace(GL_CULL_FACE);
        // glEnable(GL_CULL_FACE);
        // glEnable(GL_DEPTH_TEST);

        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
        // 绘制三角形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        if(r > 1.0f)
            increment = -0.05;
        else
            increment = 0.05;
        
        r+=increment;
    }

    // 清理资源
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    app->destory();

    return 0;

}

