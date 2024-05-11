#pragma once

#include "camera.h"

class OrthoCamera :public Camera
{
private:
   float left = 0.0f;
   float right = 0.0f;
   float top = 0.0f;
   float bottom = 0.0f;
   float near = 0.0f;
   float far = 0.0f;

public:
    OrthoCamera(glm::vec3 &position, glm::vec3 &up, glm::vec3 &right, float l, float r, float t, float b, float n, float f);
    ~OrthoCamera();

    glm::mat4 getProjectionMatrix() override;
};



