#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;

void main()
{
    int slice;
    fragColor = frontColor * texture(colorMap, vtexCoord);
}
