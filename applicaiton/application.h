#pragma once
#include<iostream>
#include "../glFramework/core.h"

/**
 * 当前应用本身
*/

#define app Application::getInstance()

using ResizeCallback = void(*)(int width, int height);
using KeyCallback = void(*)(int key, int scancode, int action, int mods);
using MouseCallback = void(*)(int button, int action, int mods);
using CursorCallback = void(*)(double xpos, double ypos);

class Application
{
private:
    static Application *instance;
    Application();

    uint32_t width{0};
    uint32_t height{0};
    GLFWwindow * window {nullptr};

    ResizeCallback frameBufferResizeCallback{nullptr};
    KeyCallback keyCallback{nullptr};
    MouseCallback mouseCallback{nullptr};
    CursorCallback cursorCallback{nullptr};

private:
    static void realFbResizeCallback(GLFWwindow* window, int width, int height);
    static void realKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void realMouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void realCursorCallback(GLFWwindow* window, double xpos, double ypos);

public:
   static Application* getInstance();

   void setResizeCallback(ResizeCallback callback){
    this->frameBufferResizeCallback = callback;
   }

   void setKeyCallback(KeyCallback callback){
    this->keyCallback = callback;
   }

   void setMouseCallback(MouseCallback callback){
    this->mouseCallback = callback;
   }

    void setCursorCallback(CursorCallback callback){
    this->cursorCallback = callback;
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

    void getCursorPosition(double *x, double *y);

    GLFWwindow* getWindow(){
        return window;
    }

    ~Application();
};


