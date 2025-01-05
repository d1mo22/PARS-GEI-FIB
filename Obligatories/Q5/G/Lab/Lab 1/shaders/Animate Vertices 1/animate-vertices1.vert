#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform float amplitude = 0.1;  
uniform float frequency = 1.0;
uniform float time;

float PI = acos(-1.0);

void main()
{
    vec3 V = vertex + normal*abs(amplitude*sin(2.0*PI*frequency*time));
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(vec3(N.z),1.0);
    vtexCoord = texCoord;
    gl_Position = modelViewProjectionMatrix * vec4(V, 1.0);
}
