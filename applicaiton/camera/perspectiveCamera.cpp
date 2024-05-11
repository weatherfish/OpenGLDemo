#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(glm::vec3 &position, glm::vec3 &up, glm::vec3 &right, float fovy, float aspect, float near, float far)
 : Camera(position, up, right)
{
    this->fovy = fovy;
    this->aspect = aspect;
    this->near = near;
    this->far = far;
}

PerspectiveCamera::~PerspectiveCamera()
{
}

glm::mat4 PerspectiveCamera::getProjectionMatrix()
{
    //fovy角度需要转弧度
    return glm::perspective(glm::radians(fovy), aspect, near, far);
}