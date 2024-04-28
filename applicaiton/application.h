#pragma once
#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * 当前应用本身
*/

#define app Application::getInstance()

using ResizeCallback = void(*)(int width, int height);

class Application
{
private:
    static Application *instance;
    Application();

    uint32_t width{0};
    uint32_t height{0};
    GLFWwindow * window {nullptr};

    ResizeCallback frameBufferResizeCallback{nullptr};

private:
    static void realFbResizeCallback(GLFWwindow* window, int width, int height);

public:
   static Application* getInstance();

   void setResizeCallback(ResizeCallback callback){
    this->frameBufferResizeCallback = callback;
   }

    bool init(const uint32_t width = 800, const uint32_t height = 600);

    bool update();

    void destory();
    
    uint32_t getWidth(){
        return width;
    }
    
    uint32_t getHeight(){
        return height;
    }

    GLFWwindow* getWindow(){
        return window;
    }

    ~Application();
};


