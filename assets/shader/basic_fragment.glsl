#version 330 core

layout(location=0)out vec4 color;
in vec3 vColor;
in vec3 position;
in vec2 uv;

uniform float time;
uniform sampler2D sampler;
uniform sampler2D sampler2;
uniform sampler2D sampler3;

void main() 
{
    // float intensity = (sin(time)+1.0)/2.0;
    // color = vec4(vColor+intensity, 1.0);
    // color = vec4(position, 1.0);
    // vec4 c1 = texture(sampler, uv);
    // vec4 c2 = texture(sampler2, uv);
    // vec4 c3 = texture(sampler3, uv);
    // float weight = c3.r;
    // vec4 fc = mix(c1, c2, weight); // -> c1* (1-weight) + c2 * weight
    // color = vec4(fc.rgb, 1.0);
    color = texture(sampler, uv);
}