#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec4 frontColor;
out vec3 Veye;
out vec3 Neye;
out vec3 Leye;
out vec3 Lworld;
out vec3 Nworld;
out vec3 Vworld;


uniform vec4 lightPosition;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewMatrixInverse;


void main() {
    Neye = normalize(normalMatrix * normal);
    vec3 Peye = (modelViewMatrix * vec4(vertex,1.0)).xyz;
    Leye = lightPosition.xyz - Peye;
    Veye = vec3(0,0,0) - Peye;

    Nworld = normal;
    vec3 Pworld = vertex.xyz;
    Lworld = (modelViewMatrixInverse*lightPosition).xyz - Pworld;
    Vworld = (modelViewMatrixInverse*vec4(0,0,0,1)).xyz - Pworld;

    frontColor = vec4(color,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}