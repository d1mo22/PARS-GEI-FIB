#version 330 core

in vec4 frontColor;
in vec3 fvertex;

out vec4 fragColor;

uniform sampler2D panorama;

const float PI = 3.141592;

void main()
{
    // Normalizar el vector del vértice
    vec3 vtx = normalize(fvertex);
    // Calcular los ángulos esféricos
    float phi = asin(vtx.y);
    float theta = atan(vtx.z, vtx.x);
    float s = theta/(2*PI);
    float t = (phi / PI) + 0.5;
    // Convertir los ángulos a coordenadas de textura
    fragColor = texture(panorama, vec2(s,t));
}
