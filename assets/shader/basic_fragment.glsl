#version 330 core

layout(location=0)out vec4 color;
in vec3 vColor;
in vec3 position;

uniform float time;

void main() 
{
    float intensity = (sin(time)+1.0)/2.0;
    color = vec4(vColor+intensity, 1.0);
    // color = vec4(position, 1.0);
}