#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;

out vec4 fragColor;

uniform sampler2D fons;
uniform sampler2D noise1;
uniform float time;

void main()
{
    // Calcular las coordenadas de textura modificadas basadas en el tiempo
    float s = 0.08 * time + vtexCoord.s;
    float t = 0.07 * time + vtexCoord.t;
    
    // Obtener el color de la textura noise1 usando las coordenadas modificadas
    vec4 n = texture(noise1, vec2(s, t));
    
    // Usar solo los canales r y g de la textura noise1
    vec2 perturbation = n.rg * vec2(0.003, -0.005);
    
    // Calcular las nuevas coordenadas de textura para acceder a la textura fons
    vec2 newTexCoord = vtexCoord + perturbation;
    
    // Obtener el color del fragmento de la textura fons usando las nuevas coordenadas de textura
    vec4 backgroundColor = texture(fons, newTexCoord);
    
    // Calcular el color final del fragmento
    fragColor = frontColor * backgroundColor;
}
