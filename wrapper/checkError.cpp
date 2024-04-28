#include "checkError.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>


void GLClearError(){
    while (glGetError()!= GL_NO_ERROR)
    {
        
    }
}

bool GLLogCheck(const char* function){
    while (GLenum err = glGetError())
    {
        std::cout<< "OpenGL Error: "<< err << function<<std::endl;
        return false;
    }
    return true;
}