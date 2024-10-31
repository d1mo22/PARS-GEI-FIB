#version 330 core

in vec4 frontColor;
in vec2 st;
out vec4 fragColor;

uniform sampler2D digits;

void main()
{
    // Número a pintar
                        
    int number[8] = int[](2, -1, 4, 3, 5, -1, -1, 1);
    
    // Dividir la textura en subregiones
    float s = 1.0 / 10.0;
    
    // Coordenades de textura ajustades per a cada dígit
    vec2 digitCoord = vec2(st.x * s, st.y);
    
    // Inicialitzar el color del fragment
    
    vec2 digitPos = vec2(number[int(st.s)] * s, 0.0);
    vec4 digitColor = texture(digits, digitCoord + digitPos);
    if (digitColor.a < 0.5) discard;
    else fragColor = digitColor * vec4(0,0,1,1);
    //fragColor = digitColor;

}
