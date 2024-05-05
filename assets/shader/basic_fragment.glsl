#version 330 core

layout(location=0)out vec4 color;
in vec3 vColor;

void main() 
{
    color = vec4(vColor.r, vColor.g, vColor.b, 1.0);
}