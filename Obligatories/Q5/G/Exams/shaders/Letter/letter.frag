#version 330 core

in vec4 frontColor;
in vec2 st;
out vec4 fragColor;

void main()
{
    // Tamaño del mosaico (ajusta según sea necesario)
    float tileSize = 0.1;

    // Coordenadas de textura ajustadas para el mosaico
    vec2 tileCoord = mod(st, tileSize) / tileSize;

    // Centro del círculo en cada mosaico
    vec2 centre = vec2(0.5);

    // Calcular la distancia al centro del círculo
    float dist = distance(tileCoord, centre);

    // Inicializar el color del fragmento
    fragColor = vec4(0.7, 0.7, 0.7, 1.0); // Color de fondo (gris)

    // Pintar el círculo solo si la coordenada s está cerca de 0.2
    if (abs(st.s - 0.9) < 0.1 && dist < 0.5) {
        fragColor = vec4(0.0, 0.0, 0.0, 1.0); // Color del círculo (negro)
    }
}
