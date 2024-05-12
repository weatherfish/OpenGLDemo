#pragma once

#include "camera_control.h"

class TrackerBallControl : public CameraControl
{
    
private:
   
public:
    TrackerBallControl(Camera *camera);

    ~TrackerBallControl();

    void onMouse(int button, int action, double xpos, double ypos) override;

    void onCursor(float xpos, float ypos) override;

    void onKey(int key, int action, int mods) override;

    void update() override; //每一帧执行
};


