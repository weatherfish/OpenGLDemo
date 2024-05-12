#include "camera_control.h"
#include <iostream>

CameraControl::CameraControl(Camera *camera)
{
    this->camera = camera;
}

CameraControl::~CameraControl()
{
}

void CameraControl::onMouse(int button, int action, double xpos, double ypos)
{
    bool pressed = action == GLFW_PRESS; //是否按下按键
    if(pressed)
    {
        currentX = xpos;
        currentY = ypos;
    }

    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        leftMouseDown = pressed;
        break;
    
    case GLFW_MOUSE_BUTTON_RIGHT:
        rightMouseDown = pressed;
        break;
    }
}

void CameraControl::onCursor(float xpos, float ypos)
{
    
}

void CameraControl::onKey(int key, int action, int mods)
{
    if(action == GLFW_REPEAT)//去重
    {
        return;
    }
    bool pressed = action == GLFW_PRESS;
    keyMap[key] = pressed;
}

void CameraControl::update()
{
    
}