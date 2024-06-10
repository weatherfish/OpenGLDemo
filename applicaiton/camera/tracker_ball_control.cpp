#include "tracker_ball_control.h"

TrackerBallControl::TrackerBallControl(Camera *camera) : CameraControl(camera)
{

}

TrackerBallControl::~TrackerBallControl()
{

}

void TrackerBallControl::onMouse(int button, int action, double xpos, double ypos)
{
    std::cout<<"onMouse"<< xpos <<","<<ypos<<std::endl;
    CameraControl::onMouse(button, action, xpos, ypos);
}

void TrackerBallControl::onCursor(float xpos, float ypos)
{
    std::cout<<"onCursor"<< xpos <<","<<ypos<<std::endl;
    camera->getViewMatrix({sensitivity * (xpos - currentX), sensitivity * (ypos - currentY), 1.0f});
    
}

void TrackerBallControl::onKey(int key, int action, int mods)
{
    CameraControl::onKey(key, action, mods);
}

void TrackerBallControl::update()
{
    if (isLeftMouseDown())
    {
        std::cout<<"333"<<std::endl;
    }
    else if (isRightMouseDown())
    {
        std::cout<<"555"<<std::endl;
    }
}