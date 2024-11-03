#version 330 core

in vec4 frontColor;
in vec2 st;
out vec4 fragColor;

uniform sampler2D fbm;
uniform float time;

const float pi = 3.141559;
const vec4 red = vec4(1,0,0,1);
const vec4 yellow = vec4(1,1,0,1);
const vec4 green = vec4(0,1,0,1);
const vec4 cyan = vec4(0,1,1,1);
const vec4 blue = vec4(0,0,1,1);
const vec4 magenta = vec4(1,0,1,1);

void main()
{
    float r = texture(fbm, st).r;
    float f = 1*sin(2*pi*0.1*time + 2*pi*r);
    vec4 color = vec4(0);

    if (f < (-2/3.0)) {
        float t =(f + 1) / (1/3.0);
        color = mix(red, yellow, t);
    }
    else if (f < (-1/3.0)) {
        float t = ((f + 2/3.) / ((-1/3.0) + 2/3.0));
        color = mix(yellow, green, t);
    }
    else if (f < 0) {
        float t = ((f + 1/3.0) / (1/3.0));
        color = mix(green, cyan, t);
    }
    else if (f < 1/3.0) {
        float t = (f / (1/3.0));
        color = mix(cyan, blue, t);
    }
    else if (f < 2/3.0) {
        float t = ((f - 1/3.0) / (1/3.0));
        color = mix(blue, magenta, t);
    }
    else {
        color = mix(magenta, red, 3*(f-2/3.));
    }
    fragColor = color;
}
