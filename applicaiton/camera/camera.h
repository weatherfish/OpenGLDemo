#pragma once

#include "../../glFramework/core.h"

class Camera
{
public:
    glm::vec3 positionVec3{0.0f, 0.0f, 1.0f};
    glm::vec3 upVec3{0.0f, 1.0f, 0.0f};
    glm::vec3 rightVec3{1.0f, 0.0f, 0.0f};
    
public:
    Camera(glm::vec3 &position, glm::vec3 &up, glm::vec3 &right);
    ~Camera();

    glm::mat4 getViewMatrix();
    virtual glm::mat4 getProjectionMatrix();
};

