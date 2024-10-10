#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n;

void main()
{
    float y = gl_FragCoord.y;
    if (int(mod(y,n)) != 0) discard;
    fragColor = frontColor;
}
