#version 330 core

layout(location=0)in vec4 aPosition;
layout(location=1)in vec2 aUv;
layout(location=2)in vec3 aColor;

uniform float time;
uniform float speed;

out vec3 vColor;
out vec3 position;
out vec2 uv;

void main()
{
    float dx = 0.3;
    float offsetX = sin(time * speed) * dx;
    float deltal = time * 0.2;
    gl_Position=vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
    vColor = aColor * (cos(time) + 1.0f)/2.0f;
    position = aPosition.xyz;
    uv = vec2(aUv.x + deltal, aUv.y);
}