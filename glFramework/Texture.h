#pragma once

#include "core.h"
#include <string>

class Texture
{
private:
    GLuint texture {0};
    int width {0};
    int height {0};
    unsigned int unit {0};

public:
    Texture(std::string &path, unsigned int unit);
    ~Texture();

    void bind();
};


