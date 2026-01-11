#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform float time;

void main()
{   
    float temps = mod(time, 3.5);

    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z);
    vtexCoord = texCoord;
    vec3 pos;
    float t;
    if (temps < 0.5) {
         t = (temps/0.5)*(temps/0.5)*(temps/0.5);
        pos = mix(vec3(0,0,0), vertex, t);
    }
    else {
        t = (temps - 0.5) / (3.5 - 0.5);
        pos = mix(vertex, vec3(0,0,0), t);
    }
    gl_Position = modelViewProjectionMatrix * vec4(pos, 1.0);
}
