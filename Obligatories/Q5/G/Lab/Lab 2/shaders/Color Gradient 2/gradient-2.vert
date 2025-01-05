#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    vec3 N = normalize(normalMatrix * normal);

    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 yellow = vec3(1.0, 1.0, 0.0);
    vec3 green = vec3(0.0, 1.0, 0.0);
    vec3 cyan = vec3(0.0, 1.0, 1.0);
    vec3 blue = vec3(0.0, 0.0, 1.0);

    vtexCoord = texCoord;
    vec4 vertice_clip = modelViewProjectionMatrix * vec4(vertex,1.0);
    vec3 vertice_ndc = (vertice_clip.xyz / vertice_clip.w);
    float t = (vertice_ndc.y + 1.0) / 2.0;

    vec3 interpolatedColor;
    if (t < 0.25) {
        interpolatedColor = mix(red, yellow, t / 0.25);
    } else if (t < 0.5) {
        interpolatedColor = mix(yellow, green, (t - 0.25) / 0.25);
    } else if (t < 0.75) {
        interpolatedColor = mix(green, cyan, (t - 0.5) / 0.25);
    } else {
        interpolatedColor = mix(cyan, blue, (t - 0.75) / 0.25);
    }

    frontColor = vec4(interpolatedColor,1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
