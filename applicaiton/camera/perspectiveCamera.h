#pragma once

#include "camera.h"

class PerspectiveCamera : public Camera
{
private:
    float fovy = 0.0f;
    float aspect = 0.0f;
    float near = 0.0f;
    float far = 0.0f;

public:
    PerspectiveCamera(glm::vec3 &position, glm::vec3 &up, glm::vec3 &right, float fovy, float aspect, float near, float far);
    PerspectiveCamera(float fovy, float aspect, float near, float far);
    ~PerspectiveCamera();

    glm::mat4 getProjectionMatrix() override;
};
