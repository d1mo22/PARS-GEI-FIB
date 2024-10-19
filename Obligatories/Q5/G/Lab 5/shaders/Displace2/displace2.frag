#version 330 core

in vec2 st;

out vec4 fragColor;

uniform sampler2D heightMap;
uniform float smoothness = 25.0;
uniform mat3 normalMatrix;

void main()
{
    float epsilon = 1.0/128;
    float r = texture(heightMap, st).r;
    float x = texture(heightMap, st + vec2(epsilon, 0)).r;
    float y = texture(heightMap, st + vec2(0, epsilon)).r;
    vec2 G = vec2 ((x-r)/ epsilon, (y-r)/epsilon);
    vec3 N = (normalize(vec3(-G.x, -G.y, smoothness)));
    vec3 N_eyespace = normalMatrix * N;
    fragColor = vec4(N_eyespace.z);

}
