#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

void main()
{
    float f = texture(noise0, vtexCoord).x;
    vec4 rockColor = texture(rock1, vtexCoord);
    vec4 grassColor = texture(grass2, vtexCoord);
    
    // Mezclar las texturas rock1 y grass2 basándose en el valor de f
    vec4 mixedColor = mix(rockColor, grassColor, f);
    
    fragColor = mixedColor;
}
