#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float speed; //speed units in rad/s
uniform float time;

void main()
{
    //angle in radians
    //-time is for the rotation to be clockwise
    float angle = -time * speed;
    //rotation matrix around the y-axis
    mat3 rotation = mat3(
        vec3(cos(angle), 0, sin(angle)),
        vec3(0, 1, 0),
        vec3(-sin(angle), 0, cos(angle))
    );
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(rotation*vertex, 1.0);
}
