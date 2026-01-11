#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float angle = 0.5;
//neck starts 1.45 and ends 1.55
void main()
{
    vec3 vertice = vertex;
    float t = smoothstep(1.45, 1.55, vertice.y);

    mat3 rotation = mat3(
        vec3(cos(-angle), 0, sin(-angle)),
        vec3(0, 1, 0),
        vec3(-sin(-angle), 0, cos(-angle))
    );
    vec3 rotatedVertex = rotation*vertex;
    vertice = mix(vertice, rotatedVertex, t);

    vec3 normalRotada = rotation*normal;
    vec3 N = mix(normal, normalRotada, t);
    N = normalize(normalMatrix * N);
    
    frontColor = vec4(vec3(N.z),1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(vertice, 1.0);
}
