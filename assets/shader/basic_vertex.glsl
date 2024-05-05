#version 330 core

layout(location=0)in vec4 aPosition;
layout(location=1)in vec3 aColor;

uniform float time;
uniform float speed;

out vec3 vColor;
out vec3 position;

void main()
{
    float dx = 0.3;
    float offsetX = sin(time * speed) * dx;
    gl_Position=vec4(aPosition.x + offsetX, aPosition.y, aPosition.z, 1.0);
    vColor = aColor * (cos(time) + 1.0f)/2.0f;
    position = aPosition.xyz;
}