#include "Shader.h"
#include "../wrapper/checkError.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

Shader::Shader(const char* vertexPath, const char*  fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch(const std::ifstream::failure& e)
    {
        std::cout << "Error Shader File"<<e.what() << '\n';
    }

   progrem = CreateShader(vertexCode, fragmentCode);
}

Shader::~Shader()
{

}

void Shader::begin(){
    GLCall(glUseProgram(progrem));
}
void Shader::end(){
    GLCall(glUseProgram(0));
}

void Shader::setFloat(const std::string& name, float value){
    int location = glGetUniformLocation(progrem, name.c_str());
    GLCall(glUniform1f(location, value));
}


unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"Failed to compile "<<(type == GL_VERTEX_SHADER? "vertex" : "fragment") <<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragShader)
{
    unsigned int program =  glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    checkShaderError(program, ShaderCheckType::Link);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

ShaderProgremSource Shader::parseShader(const std::string file)
{
    std::ifstream stream(file);
    std::string line;

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    ShaderType type = ShaderType::NONE;

    std::stringstream ss[2];
    while (getline(stream, line))
    {   
        if(line.find("#shader") != std::string::npos){
             if(line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
             }
            else if (line.find("fragment") != std::string::npos)
             {
                type = ShaderType::FRAGMENT;
             }
        }else{
            ss[(int)type] <<line<<'\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
    
}


void Shader::checkShaderError(GLuint target, ShaderCheckType type)
{
    int success;
    char infoLog[1024];

    if(type == ShaderCheckType::Compile)
    {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(target, 1024, NULL, infoLog);
            std::cout<<"Error Shader Compile :"<<infoLog<<std::endl;
        }
    }
    else if (type == ShaderCheckType::Link)
    {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(target, 1024, NULL, infoLog);
            std::cout<<"Error Shader Link :"<<infoLog<<std::endl;
        }
    }else{
        std::cout<<"Check Error"<<std::endl;
    }
    
}
