#pragma once

#include "core.h"
#include <string>

struct ShaderProgremSource{
    std::string VertexSource;
    std::string FragSource;
};

enum ShaderCheckType{
    Compile,
    Link,
};

class Shader
{
private:
    GLuint progrem;

    void checkShaderError(GLuint target, ShaderCheckType type);
   
public:
    Shader(const char* vertexPath, const char* fragmentPath);

    ~Shader();

    void begin(); //开始使用

    void end(); //结束使用

    void setFloat(const std::string& name, float value);

    void setFloat(const std::string& name, float x, float y, float z);

    void setInt(const std::string& name, int value);

    void setMat(const std::string &name, float data[], int count);

    void setMatrix4x4(const std::string &name, glm::mat4 value);

    void setMatrix4x4(const std::string &name, glm::mat4 value, int count);


    unsigned int CompileShader(const std::string& source, unsigned int type);

    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragShader);

    ShaderProgremSource parseShader(const std::string file);        

};


