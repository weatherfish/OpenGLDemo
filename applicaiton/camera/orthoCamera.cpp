#include "orthoCamera.h"

OrthoCamera::OrthoCamera(glm::vec3 &position, glm::vec3 &up, glm::vec3 &right, float l, float r, float t, float b, float n, float f)
 : Camera(position, up, right)
 {
    this->left = l;
    this->right = r;
    this->top = t;
    this->bottom = b;
    this->near = n;
    this->far = f;
}

OrthoCamera::~OrthoCamera()
{

}

 glm::mat4 OrthoCamera::getProjectionMatrix()
 {
    return glm::ortho(left, right, top, bottom, near, far);
 }