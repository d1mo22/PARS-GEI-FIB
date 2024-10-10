#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    float fraction = 1/8.;
    vec4 grey = vec4(0.8);

    int x = int (mod(vtexCoord.x/fraction,2));
    int y = int (mod(vtexCoord.y/fraction,2));

    if (x == y) fragColor = grey;
    else fragColor = vec4(vec3(0.0),1.0);
}
