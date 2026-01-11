#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

uniform mat4 modelViewProjectionMatrix;

uniform sampler2D heighMap;
uniform float scale = 0.05;

out vec2 st;

void main() {
    st = 0.49 * vertex.xy + vec2(0.5);
    float height = texture(heighMap, st).r;
    vec3 vertexPrima = vertex + normal * scale * height;
    gl_Position = modelViewProjectionMatrix * vec4(vertexPrima, 1.0);
}
