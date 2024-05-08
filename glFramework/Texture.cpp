#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(std::string &path, unsigned int unit)
{
    this->unit = unit;
    int channels;

    ///翻转y轴
    stbi_set_flip_vertically_on_load(true);

    // unsigned char* data = stbi_load("assets/textures/1.png", &width, &height, &channels, STBI_rgb_alpha);
    // unsigned char* data = stbi_load("assets/textures/2.jpg", &width, &height, &channels, STBI_rgb_alpha);
    unsigned char* data = stbi_load(path.c_str(), &this->width, &this->height, &channels, STBI_rgb_alpha);

    //生成纹理
    glGenTextures(1, &this->texture);
    //激活纹理单元 0-15
    glActiveTexture(GL_TEXTURE0 + unit);
    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, this->texture);
    //传输纹理数据  同时会开辟显存
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //释放数据
    stbi_image_free(data);
    //设置纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //大于使用线性插值
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //小于取附近值
    //设置纹理包裹
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    ///多级渐远纹理
    
}

Texture::~Texture()
{
    if(this->texture != 0){
        glDeleteTextures(1, &this->texture);
    }
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}
