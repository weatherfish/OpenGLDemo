#include "camera.h"

Camera::Camera(glm::vec3 &position, glm::vec3 &up, glm::vec3 &right)
{
    this->positionVec3 = position;
    this->upVec3 = up;
    this->rightVec3 = right;
}

Camera::~Camera()
{

}


 glm::mat4 Camera::getViewMatrix()
 {
    glm::vec3 eye = positionVec3;

    glm::vec3 front = glm::cross(upVec3, rightVec3);
    glm::vec3 center = positionVec3 + front;

    return glm::lookAt(eye, center, upVec3);
 }

glm::mat4 Camera::getProjectionMatrix(){
    return glm::identity<glm::mat4>();
}