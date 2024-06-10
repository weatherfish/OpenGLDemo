#pragma once

#include <iostream>
#include <map>
#include "camera.h"

class CameraControl
{
protected:
    bool leftMouseDown = false;
    bool rightMouseDown = false;

    float currentX =0.0f;
    float currentY =0.0f;

    std::map<int,bool> keyMap; //此时哪些按键被按下

    float sensitivity = 0.2f;

    Camera * camera = nullptr;

public:
    CameraControl(Camera *camera);
    ~CameraControl();

    std::map<int,bool> getKeyMap()
    {
        return keyMap;
    }

    float isLeftMouseDown()
    {
        return leftMouseDown;
    }

    float isRightMouseDown()
    {
        return rightMouseDown;
    }

    float getCurrentX()
    {
        return currentX;
    }

    float getCurrentY()
    {
        return currentY;
    }

    void setSensitivity(float value){
        this->sensitivity = value;
    }

    void setCamera(Camera* camera)
    {
        this->camera = camera;
    }

    virtual void onMouse(int button, int action, double xpos, double ypos);

    virtual void onCursor(float xpos, float ypos);

    virtual void onKey(int key, int action, int mods);

    virtual void update(); //每一帧执行

};

