#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec3 fnormal;
out vec3 V;
out vec3 fvertex;
out vec3 bbMin, bbMax;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix, modelViewMatrix, modelViewMatrixInverse;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMax, boundingBoxMin;

void main()
{
    fnormal = normal;
    fvertex = vertex;
    V = normalize((modelViewMatrixInverse * vec4(0,0,0,1)).xyz - vertex);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
