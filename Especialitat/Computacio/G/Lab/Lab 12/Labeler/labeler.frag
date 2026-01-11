#version 330 core

in vec4 gfrontColor;
in vec2 gtexCoord;
out vec4 fragColor;

void main()
{
    if (gfrontColor == vec4(1,1,0,1)) {
        bool insideF = false;
        
        // Línea vertical de la F
        if (gtexCoord.x >= 2.0 && gtexCoord.x <= 3.0 && gtexCoord.y >= 1.0 && gtexCoord.y <= 6.0) 
            insideF = true;
        // Línea horizontal superior
        if (gtexCoord.x >= 2.0 && gtexCoord.x <= 5.0 && gtexCoord.y >= 5.0 && gtexCoord.y <= 6.0) 
            insideF = true;
        // Línea horizontal media
        if (gtexCoord.x >= 3.0 && gtexCoord.x <= 4.0 && gtexCoord.y >= 3.0 && gtexCoord.y <= 4.0) 
            insideF = true;
            
        if (insideF)
            fragColor = vec4(0,0,0,1);
        else
            fragColor = vec4(1,1,0,1);
    }
    else {
        fragColor = gfrontColor;
    }
}