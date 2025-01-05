#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
    float fraction = 1/n;
    int x = int (mod(vtexCoord.x/fraction, 2));
    int y = int (mod(vtexCoord.y/fraction, 2));
    if (x == y) fragColor = vec4(0.8);
    else fragColor = vec4(0.0);
}
