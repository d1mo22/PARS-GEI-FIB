#version 330 core

in vec4 frontColor;
in vec2 st;
in vec3 N;
out vec4 fragColor;

uniform sampler2D colormap;

void main()
{
    vec3 normal = normalize(N);
    vec2 C1 = vec2(0.34, 0.65) -0.1*normal.xy;
    vec2 C2 = vec2(0.66, 0.65) -0.1*normal.xy;
    if (distance(st, C1) < 0.05 || distance(st, C2) < 0.05) fragColor = vec4(0);
    else fragColor = texture(colormap, st);
}
