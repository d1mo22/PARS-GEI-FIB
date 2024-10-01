#version 330 core

in vec4 frontColor;
in float x;
out vec4 fragColor;

uniform float time;
void main()
{
    if (x > time) discard;
    fragColor = vec4(0,0,1,1);
}
