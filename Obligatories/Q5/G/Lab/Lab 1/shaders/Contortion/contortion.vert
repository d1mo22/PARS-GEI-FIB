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
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;

    //angle = (y-0.5)*sin(t) -> y equals y coord object space
    float angle = (vertex.y - 0.5) * sin(time);
    
    mat3 rotation_x = mat3(
        1, 0, 0,
        0, cos(angle), sin(angle),
        0, -sin(angle), cos(angle)
    ); 

    vec3 aux = vec3(vertex);
    if (aux.y >= 0.5) {
        aux = aux - vec3(0,1,0);
        aux = rotation_x * aux;
       aux = aux + vec3(0,1,0);
    }
    gl_Position = modelViewProjectionMatrix * vec4(aux, 1.0);
}
