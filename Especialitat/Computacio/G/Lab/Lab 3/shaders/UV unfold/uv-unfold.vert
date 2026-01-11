#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec2 Min = vec2(-1,-1);
uniform vec2 Max = vec2(1,1);

void main()
{
    frontColor = vec4(color,1.0);
    // Normalizar las coordenadas de textura al rango [0, 1]
    float x = (texCoord.x - Min.x) / (Max.x - Min.x);
    float y = (texCoord.y - Min.y) / (Max.y - Min.y);
    // Escalar al rango [0, 2]
    x *= 2;
    y *= 2;
    // Trasladar al rango [-1, 1]
    x -= 1;
    y -= 1;

    gl_Position = vec4(x,y,0,1);
}
