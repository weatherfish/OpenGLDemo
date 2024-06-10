#pragma once

// #include <assert.h>

#ifdef DEBUG
#define GLCall(func) GLClearError();func;assert(GLLogCheck(#func));
#else
#define GLCall(func) func 
#endif


 void GLClearError();

 bool GLLogCheck(const char* function);