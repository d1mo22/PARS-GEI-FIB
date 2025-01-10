#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int mode = 1;

void main()
{
    // Inicializar valor de iluminación
    float illumination = frontColor.x;
    
    if (mode == 2) {
        // Obtener parte entera de coordenadas
        float x = floor(gl_FragCoord.x);
        float y = floor(gl_FragCoord.y);
        
        // Ajustar iluminación según paridad
        if (mod(x, 2.0) == 0.0 && mod(y, 2.0) == 0.0) 
            illumination -= 0.5;  // x,y pares
        else if (mod(x, 2.0) == 0.0) 
            illumination += 0.25; // x par, y impar
        else if (mod(x, 2.0) == 1.0 && mod(y, 2.0) == 1.0) 
            illumination -= 0.25; // x,y impares
        // caso x impar, y par -> +0 (no necesita código)
    }
    
    // Aplicar umbral
    fragColor = (illumination < 0.5) ? vec4(0.0) : vec4(1.0);
}