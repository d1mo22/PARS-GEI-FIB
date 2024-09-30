#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;
uniform vec3 boundingBoxMax;
uniform vec3 boundingBoxMin;
uniform vec2 viewport;
uniform vec2 mousePosition;
uniform float radius = 300;
uniform int test = 0;

vec2 getMousePositionWindowSpace() {
    if(test == 0) return mousePosition;
    if(test == 1) return vec2(400,520);
    if(test == 2) return vec2(600,225);
    if(test == 3) return vec2(200,375);
    return vec2(400,300);
}

vec2 ToWindowSpace() {
    vec4 clipping = modelViewProjectionMatrix * vec4(vertex,1.0);
    vec3 ncd = clipping.xyz / clipping.w;
    vec2 window = (ncd.xy * 0.5 + 0.5) * viewport;
    return window;
}

void main()
{
    float distancia = length(boundingBoxMax - boundingBoxMin);
    vec3 P_eye = mat3(modelViewMatrix) * vertex;
    vec3 N = normalize(normalMatrix * normal);
    vec3 P_prime = P_eye + N * 0.03*distancia;
    vec2 P_window = ToWindowSpace();

    float mouseDist = length(getMousePositionWindowSpace() - P_window);
    float t = smoothstep(0.8*radius, 0.05*radius, mouseDist);
    vec3 vertice = mix(P_eye, P_prime, t);

    vec3 white = vec3(1,1,1);
    vec3 red = vec3(1,0,0);
    vec3 colorM = mix(white, red, t);
    frontColor = vec4(colorM,1.0) * N.z;
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertice, 1.0);
}
