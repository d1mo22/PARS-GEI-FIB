#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
uniform float time;

vec2 eyePosition = vec2(0.393, 0.652);
vec2 mouthOffset = vec2(0.057,- 0.172);

void main()
{
    if (fract(time) <= 0.5)  fragColor = texture(colorMap, vtexCoord);
    else {
        float dist = length(vtexCoord - eyePosition);
        if (dist <= 0.025) fragColor = texture(colorMap, vtexCoord + mouthOffset);
        else fragColor = texture(colorMap, vtexCoord);
    }
   
}
