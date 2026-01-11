#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float lambda

void main()
{
    vec4 color = mix(vec4(1,0,0,1), vec4(0,1,0,1), lambda);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z * color);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
