#version 330 core

uniform sampler2D colorMap;
uniform float fps = 30.0;
uniform float time;

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
    float s = 1./8.;
    float t = 1./6.;
    
    int frame = int(mod(time * fps, 48));

    vec2 Position = vec2(mod(frame, 8) * s , (5 - frame/8) * t);

    fragColor = texture(colorMap,(vtexCoord * vec2(s,t)) + Position);
    fragColor = fragColor * fragColor.a;

    
}